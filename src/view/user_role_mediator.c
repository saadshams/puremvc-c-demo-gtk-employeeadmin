#include "user_role_mediator.h"

#include "employee_admin/i_user_role.h"
#include "view/components/user_role.h"

static void onRegister(struct IMediator *self) {
    struct UserRole *component = self->getComponent(self);
    // component->setDelegate(component, (struct IUserRole){ .context = self });
}

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {

}

struct IMediator *user_role_mediator_init(void *buffer, const char *name, void *component) {
    struct IMediator *mediator = puremvc_mediator_init(buffer, name, component);
    mediator->onRegister = onRegister;
    mediator->listNotificationInterests = listNotificationInterests;
    mediator->handleNotification = handleNotification;
    return mediator;
}

struct UserRoleMediator *user_role_mediator_bind(struct UserRoleMediator *mediator, struct IMediator *super) {
    mediator->super = super;

    return mediator;
}