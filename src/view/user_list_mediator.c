#include "user_list_mediator.h"

#include "application_facade.h"
#include "model/user_proxy.h"
#include "view/components/user_list.h"

#include <puremvc/puremvc.h>

static void set_component(const struct UserListMediator *self, void *component) {
    struct IMediator *super = self->super;
    super->set_component(super, component);
    user_list_set_delegate((struct IUserList) {
        .context = super,
        .find_all = (struct IArray *(*) (void *)) self->find_all,
        .on_new = (void (*) (void *, const void *)) self->on_new,
        .on_delete = (void (*) (void *, const void *)) self->on_delete,
        .on_select = (void (*) (void *, const void *)) self->on_select
    });
    user_list_run();
}

static const char *const *list_notification_interests(const struct IMediator *self) {
    (void) self;
    static const char *interests[] = { USER_UPDATED, NULL };
    return interests;
}

static void handle_notification(const struct IMediator *self, struct INotification *notification) {
    const char *name = notification->get_name(notification);
    if (strcmp(name, USER_UPDATED) == 0) {
        user_list_refresh(notification->get_body(notification));
    }
}

static struct IArray *find_all(const struct IMediator *self) {
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);

    const struct UserProxy *user_proxy = facade->retrieve_proxy(facade, UserProxy_NAME)->instance;
    return user_proxy->find_all(user_proxy);
}

static void on_new(const struct IMediator *self, const struct UserVO *user) {
    g_print("New clicked: selection cleared\n");
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);
    facade->send_notification(facade, NEW_USER, NULL, NULL);
}

static void on_delete(const struct IMediator *self, struct UserVO *user) {
    g_print("Delete clicked for user: %s, %s %s, %s, dept=%d\n", user->username, user->first, user->last, user->email, user->department);
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);
    facade->send_notification(facade, DELETE_USER, user, NULL);
}

static void on_select(const struct IMediator *self, struct UserVO *user) {
    const struct INotifier *notifier = self->get_notifier(self);
    const struct IFacade *facade = notifier->get_facade(notifier);
    facade->send_notification(facade, USER_SELECTED, user, NULL);
}

struct IMediator *user_list_mediator_new() {
    struct IMediator *mediator = puremvc_mediator_new(UserListMediator_NAME, NULL);
    mediator->list_notification_interests = list_notification_interests;
    mediator->handle_notification = handle_notification;
    return mediator;
}

struct UserListMediator *user_list_mediator_extend(struct UserListMediator *mediator, struct IMediator *super) {
    mediator->super = super;

    mediator->set_component = set_component;
    mediator->find_all = find_all;
    mediator->on_new = on_new;
    mediator->on_delete = on_delete;
    mediator->on_select = on_select;

    return mediator;
}
