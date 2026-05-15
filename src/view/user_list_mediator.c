#include "user_list_mediator.h"
#include "application_facade.h"
#include "model/user_proxy.h"
#include "view/components/user_list.h"

#include <puremvc/puremvc.h>

static void assign(const struct UserListMediator *self, void *component) {
    struct IMediator *super = self->super;
    super->setComponent(super, component);
    user_list_set_delegate((struct IUserList) {
        .context = super,
        .get_users = (size_t (*) (void *, void *, size_t)) self->get_users,
        .on_new = (void (*) (void *, void *)) self->on_new,
        .on_delete = (void (*) (void *, void *)) self->on_delete,
        .on_select = (void (*) (void *, void *)) self->on_select
    });
    user_list_run();
}

static void onRegister(struct IMediator *self) {}

static const char *const *listNotificationInterests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { NULL };
    return interests;
}

static void handleNotification(const struct IMediator *self, struct INotification *notification) {

}

static size_t get_users(const struct IMediator *self, struct UserVO **out, const size_t max) {
    const struct INotifier *notifier = self->getNotifier(self);
    const struct IFacade *facade = notifier->getFacade(notifier);

    struct IProxy *proxy = facade->retrieveProxy(facade, UserProxy_NAME);
    const struct UserProxy *userProxy = user_proxy_extend(&(struct UserProxy){}, proxy);
    return userProxy->get_users(userProxy, out, max);
}

static void on_new(const struct IMediator *self, const struct UserVO *user) {
    g_print("New clicked: selection cleared\n");
    const struct INotifier *notifier = self->getNotifier(self);
    const struct IFacade *facade = notifier->getFacade(notifier);
    facade->sendNotification(facade, NEW_USER, NULL, NULL);
}

static void on_delete(const struct IMediator *self, struct UserVO *user) {
    g_print("Delete clicked for user: %s, %s %s, %s, dept=%d\n", user->username, user->first, user->last, user->email, user->department);
    const struct INotifier *notifier = self->getNotifier(self);
    const struct IFacade *facade = notifier->getFacade(notifier);
    facade->sendNotification(facade, DELETE_USER, user, NULL);
}

static void on_select(const struct IMediator *self, struct UserVO *user) {
    g_print("Selected user: %s, %s %s, %s, dept=%d\n", user->username, user->first, user->last, user->email, user->department);

    const struct INotifier *notifier = self->getNotifier(self);
    const struct IFacade *facade = notifier->getFacade(notifier);
    facade->sendNotification(facade, USER_SELECTED, user, NULL);
}

struct IMediator *user_list_mediator_init(void *buffer, const char *name, void *component) {
    struct IMediator *mediator = puremvc_mediator_init(buffer, name, component);
    mediator->onRegister = onRegister;
    mediator->listNotificationInterests = listNotificationInterests;
    mediator->handleNotification = handleNotification;
    return mediator;
}

struct UserListMediator *user_list_mediator_extend(struct UserListMediator *mediator, struct IMediator *super) {
    mediator->super = super;

    mediator->assign = assign;
    mediator->get_users = get_users;
    mediator->on_new = on_new;
    mediator->on_delete = on_delete;
    mediator->on_select = on_select;

    return mediator;
}
