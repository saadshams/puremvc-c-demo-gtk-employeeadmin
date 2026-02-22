#include "user_list_mediator.h"

#include "model/user_proxy.h"
#include "view/components/user_list.h"

#include <puremvc/puremvc.h>

static size_t list(const struct UserListMediator *self, struct UserVO **out, const size_t max) {
    const struct IMediator *super = self->super;
    const struct IFacade *facade = super->getNotifier(super)->getFacade(super->getNotifier(super));

    struct IProxy *proxy = facade->retrieveProxy(facade, UserProxy_NAME);
    const struct UserProxy *userProxy = user_proxy_bind(&(struct UserProxy){}, proxy);
    return userProxy->list(userProxy, out, max);
}

static void registerComponent(const struct UserListMediator *self, void *component) {
    struct IMediator *super = self->super;
    super->setComponent(super, component);
    user_list_set_delegate((struct IUserList) { .context = (void *) self, .list = (size_t (*) (void *, struct UserVO **, size_t)) self->list } );
    user_list_run();
}

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {

}

struct IMediator *user_list_mediator_init(void *buffer, const char *name, void *component) {
    struct IMediator *mediator = puremvc_mediator_init(buffer, name, component);
    mediator->listNotificationInterests = listNotificationInterests;
    mediator->handleNotification = handleNotification;
    return mediator;
}

struct UserListMediator *user_list_mediator_bind(struct UserListMediator *mediator, struct IMediator *super) {
    mediator->super = super;
    mediator->list = list;
    mediator->registerComponent = registerComponent;
    return mediator;
}
