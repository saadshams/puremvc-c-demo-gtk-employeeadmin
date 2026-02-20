#include "user_list_mediator.h"

#include "view/components/user_list.h"

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {

}

static void registerComponent(const struct UserListMediator *mediator, void *component) {
    struct IMediator *self = mediator->super;
    self->setComponent(self, component);
    user_list_set_delegate((struct IUserList) { .context = self } );
}

struct IMediator *user_list_mediator_init(void *buffer, const char *name, void *component) {
    struct IMediator *mediator = puremvc_mediator_init(buffer, name, component);
    mediator->listNotificationInterests = listNotificationInterests;
    mediator->handleNotification = handleNotification;
    return mediator;
}

struct UserListMediator *user_list_mediator_bind(struct UserListMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    mediator->registerComponent = registerComponent;
    return mediator;
}
