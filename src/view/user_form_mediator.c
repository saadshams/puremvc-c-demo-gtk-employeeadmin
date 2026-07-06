#include "user_form_mediator.h"
#include "application_facade.h"
#include "components/user_form.h"

#pragma region Accessors

static void set_component(const struct UserFormMediator *self, void *component) {
    struct IMediator *mediator = self->super;
    mediator->set_component(mediator, component);

    user_form_set_delegate((struct IUserForm) {
        .context = mediator,
        .on_update = (void (*) (void *, void *)) self->on_update,
    });
}

#pragma endregion

#pragma region Notification Handling

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

#pragma endregion

#pragma region Delegate Operations

static void on_update(const struct IMediator *self, struct UserVO *user) {
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);
    facade->send_notification(facade, USER_UPDATED, user, NULL);
    user_form_reset();
}

#pragma endregion

#pragma region Memory Management

static size_t size(void) {
    return (sizeof(struct UserFormMediator) + (sizeof(void *) - 1u)) & ~(sizeof(void *) - 1u);
}

static struct UserFormMediator *alloc(void) {
    struct UserFormMediator *mediator = malloc(size());

    if (mediator == NULL) {
        fprintf(stderr, "\033[0;31m[EmployeeAdmin::UserFormMediator::alloc] ERROR: Instance allocation failed.\033[0m\n");
        return NULL;
    }

    return mediator;
}

static struct UserFormMediator *init(struct UserFormMediator *mediator) {
    if (mediator == NULL) return NULL;

    memset(mediator, 0, size());

    mediator->set_component = set_component;
    mediator->on_update = on_update;

    return mediator;
}

#pragma endregion

#pragma region Public API

struct IMediator *user_form_mediator_new(void) {
    struct IMediator *super = puremvc_mediator_new(UserFormMediator_NAME, NULL);
    if (super == NULL) return NULL;

    struct UserFormMediator *mediator = init(alloc());
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

void user_form_mediator_dealloc(struct UserFormMediator **mediator) {
    if (mediator == NULL || *mediator == NULL) return;

    struct IMediator *super = (*mediator)->super;

    puremvc_mediator_dealloc(&super); // Destroy super.

    free(*mediator); // Destroy sub.
    *mediator = NULL;
}

#pragma endregion
