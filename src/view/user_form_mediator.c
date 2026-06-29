#include "user_form_mediator.h"
#include "application_facade.h"
#include "components/user_form.h"

static void set_component(const struct UserFormMediator *self, void *component) {
    struct IMediator *super = self->super;
    super->set_component(super, component);
    user_form_set_delegate((struct IUserForm) {
        .context = super,
        .on_update = (void (*) (void *, void *)) self->on_update,
    });
}

static const char *const *list_notification_interests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { USER_SELECTED, NULL };
    return interests;
}

static void handle_notification(const struct IMediator *self, struct INotification *notification) {
    const char *name = notification->get_name(notification);
    if (strcmp(name, USER_SELECTED) == 0) {
        user_form_set_user(notification->get_body(notification));
    }
}

static void on_update(const struct IMediator *self, struct UserVO *user) {
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);
    facade->send_notification(facade, USER_UPDATED, user, NULL);
    user_form_reset();
}

struct IMediator *user_form_mediator_new() {
    struct IMediator *mediator = puremvc_mediator_new(UserFormMediator_NAME, NULL);
    mediator->list_notification_interests = list_notification_interests;
    mediator->handle_notification = handle_notification;
    return mediator;
}

struct UserFormMediator *user_form_mediator_extend(struct UserFormMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    mediator->set_component = set_component;
    mediator->on_update = on_update;
    return mediator;
}
