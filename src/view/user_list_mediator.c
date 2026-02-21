#include "user_list_mediator.h"

#include "model/user_proxy.h"
#include "model/valueObject/user_vo.h"
#include "view/components/user_list.h"

static void getUsers(const struct IMediator *self) {
    struct UserVO users[MAX_USERS] = {0};
    struct IProxy *super = user_proxy_init(alloca(puremvc_proxy_size()), "UserProxyTest", &users);
    const struct UserProxy *proxy = user_proxy_bind(&(struct UserProxy){}, super);
}

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
    user_list_set_delegate((struct IUserList) { .context = self, .getUsers = (void (*) (void *)) getUsers } );
    user_list_start();
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
