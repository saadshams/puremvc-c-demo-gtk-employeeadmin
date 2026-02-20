#include "user_role_mediator.h"

#include "components/user_role.h"

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {

}

static void registerComponent(const struct UserRoleMediator *mediator, void *component) {
    struct IMediator *self = mediator->super;
    self->setComponent(self, component);
    user_role_set_delegate((struct IUserRole) { .context = self } );
}

struct IMediator *user_role_mediator_init(void *buffer, const char *name, void *component) {
    struct IMediator *mediator = puremvc_mediator_init(buffer, name, component);
    mediator->listNotificationInterests = listNotificationInterests;
    mediator->handleNotification = handleNotification;
    return mediator;
}

struct UserRoleMediator *user_role_mediator_bind(struct UserRoleMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    mediator->registerComponent = registerComponent;
    return mediator;
}
