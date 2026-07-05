#include "user_role_mediator.h"
#include "components/user_role.h"

#pragma region Accessors

static void set_component(const struct UserRoleMediator *mediator, void *component) {
    struct IMediator *self = mediator->super;
    self->set_component(self, component);
    user_role_set_delegate((struct IUserRole) { .context = self } );
}

#pragma endregion

#pragma region Notification Handling

static const char *const *list_notification_interests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handle_notification(const struct IMediator *self, struct INotification *notification) {

}

#pragma endregion

#pragma region Public API

struct IMediator *user_role_mediator_new() {
    struct IMediator *mediator = puremvc_mediator_new(UserRoleMediator_NAME, NULL);
    mediator->list_notification_interests = list_notification_interests;
    mediator->handle_notification = handle_notification;
    return mediator;
}

struct UserRoleMediator *user_role_mediator_extend(struct UserRoleMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    mediator->set_component = set_component;
    return mediator;
}

#pragma endregion
