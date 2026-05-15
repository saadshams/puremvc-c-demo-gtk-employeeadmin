#include "user_form_mediator.h"
#include "application_facade.h"
#include "model/valueObject/user_vo.h"
#include "components/user_form.h"

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { USER_SELECTED, NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {
    const char *name = notification->getName(notification);
    if (strcmp(name, USER_SELECTED) == 0) {
        const struct UserVO *user = notification->getBody(notification);

        g_print("Notification: USER_SELECTED -> %s, %s %s, %s, dept=%d\n", user->username,
            user->first,
            user->last,
            user->email,
            user->department
        );
    }
}

static void assign(const struct UserFormMediator *mediator, void *component) {
    struct IMediator *self = mediator->super;
    self->setComponent(self, component);
    user_form_set_delegate((struct IUserForm) { .context = self } );
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
    return mediator;
}
