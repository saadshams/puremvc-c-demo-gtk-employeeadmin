#include "user_role_mediator.h"
#include "components/user_role.h"

#pragma region Accessors

static void set_component(const struct UserRoleMediator *self, void *component) {
    struct IMediator *mediator = self->super;
    mediator->set_component(mediator, component);

    user_role_set_delegate((struct IUserRole) {
        .context = mediator
    });
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

#pragma region Memory Management

static size_t size(void) {
    return (sizeof(struct UserRoleMediator) + (sizeof(void *) - 1u)) & ~(sizeof(void *) - 1u);
}

static struct UserRoleMediator *alloc(void) {
    struct UserRoleMediator *mediator = malloc(size());

    if (mediator == NULL) {
        fprintf(stderr, "\033[0;31m[EmployeeAdmin::UserRoleMediator::alloc] ERROR: Instance allocation failed.\033[0m\n");
        return NULL;
    }

    return mediator;
}

static struct UserRoleMediator *init(struct UserRoleMediator *mediator) {
    if (mediator == NULL) return NULL;

    memset(mediator, 0, size());
    mediator->set_component = set_component;
    return mediator;
}

#pragma endregion

#pragma region Public API

struct IMediator *user_role_mediator_new(void) {
    struct IMediator *super = puremvc_mediator_new(UserRoleMediator_NAME, NULL);
    if (super == NULL) return NULL;

    struct UserRoleMediator *mediator = init(alloc());
    if (mediator == NULL) {
        puremvc_mediator_dealloc(&super);
        return NULL;
    }

    super->list_notification_interests = list_notification_interests;
    super->handle_notification = handle_notification;

    // wire bidirectional references
    super->sub = mediator; // interface to subclass
    mediator->super = super; // subclass to interface

    return super;
}

void user_role_mediator_dealloc(struct UserRoleMediator **mediator) {
    if (mediator == NULL || *mediator == NULL) return;

    struct IMediator *super = (*mediator)->super;

    puremvc_mediator_dealloc(&super); // Destroy super.

    free(*mediator); // Destroy sub.
    *mediator = NULL;
}

#pragma endregion
