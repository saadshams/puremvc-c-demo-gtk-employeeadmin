#include "user_form_mediator.h"
#include "application_facade.h"
#include "components/user_form.h"

static void assign(const struct UserFormMediator *self, void *component) {
    struct IMediator *super = self->super;
    super->setComponent(super, component);
    user_form_set_delegate((struct IUserForm) {
        .context = super,
        .on_update = (void (*) (void *, void *)) self->on_update,
    });
}

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { USER_SELECTED, NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {
    const char *name = notification->getName(notification);
    if (strcmp(name, USER_SELECTED) == 0) {
        user_form_set_user(notification->getBody(notification));
    }
}

static void on_update(const struct IMediator *self, struct UserVO *user) {
    const struct INotifier *notifier = self->getNotifier(self);
    const struct IFacade *facade = notifier->getFacade(notifier);
    facade->sendNotification(facade, USER_UPDATED, user, NULL);
    user_form_reset();
}

struct IMediator *user_form_mediator_init(void *buffer, const char *name, void *component) {
    struct IMediator *mediator = puremvc_mediator_init(buffer, name, component);
    mediator->listNotificationInterests = listNotificationInterests;
    mediator->handleNotification = handleNotification;
    return mediator;
}

struct UserFormMediator *user_form_mediator_extend(struct UserFormMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    mediator->assign = assign;
    mediator->on_update = on_update;
    return mediator;
}
