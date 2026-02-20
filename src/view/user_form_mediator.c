#include "user_form_mediator.h"

#include "components/user_form.h"

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {

}

static void registerComponent(const struct UserFormMediator *mediator, void *component) {
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

struct UserFormMediator *user_form_mediator_bind(struct UserFormMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    mediator->registerComponent = registerComponent;
    return mediator;
}
