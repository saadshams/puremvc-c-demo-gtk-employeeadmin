#include "user_proxy.h"

#include <collection/i_array.h>

#pragma region Hooks

static void on_register(struct IProxy *self) {
    (void) self;
}

static void on_remove(struct IProxy *self) {
    (void) self;
}

#pragma endregion

#pragma region Operations

static bool predicate(const void *element, const void *item) {
    return strcmp(((struct UserVO *) element)->username, ((struct UserVO *) item)->username) == 0;
}

static struct IArray *find_all(const struct UserProxy *self) {
    const struct IProxy *super = self->super;
    return super->get_data(super);;
}

static bool save(const struct UserProxy *self, const struct UserVO *user) {
    const struct IProxy *super = self->super;
    struct IArray *users = super->get_data(super);

    if (users->find(users, predicate, user) != NULL)
        return false;

    users->push(users, user);
    return true;
}

static bool update(const struct UserProxy *self, const struct UserVO *user) {
    const struct IProxy *super = self->super;
    struct IArray *users = super->get_data(super);

    const size_t index = users->first_index(users, predicate, user);;
    if (index == SIZE_MAX) return false;

    struct UserVO *existing = users->put(users, user, index);
    free(existing);

    return true;
}

static bool delete(const struct UserProxy *self, const struct UserVO *user) {
    const struct IProxy *super = self->super;
    struct IArray *users = super->get_data(super);

    struct UserVO *removed = users->remove_item(users, user);
    if (removed != NULL) {
        free(removed);
        return true;
    }

    return false;
}

#pragma endregion

#pragma region Memory Management

static size_t size(void) {
    return (sizeof(struct UserProxy) + (sizeof(void *) - 1u)) & ~(sizeof(void *) - 1u);
}

static struct UserProxy *alloc(void) {
    struct UserProxy *proxy = malloc(size());

    if (proxy == NULL) {
        fprintf(stderr, "\033[0;31m[EmployeeAdmin::UserProxy::alloc] ERROR: Instance allocation failed.\033[0m\n");
        return NULL;
    }

    return proxy;
}

static struct UserProxy *init(struct UserProxy *proxy) {
    if (proxy == NULL) return NULL;

    memset(proxy, 0, size());

    proxy->find_all = find_all;
    proxy->save = save;
    proxy->update = update;
    proxy->delete = delete;

    return proxy;
}

#pragma endregion

#pragma region Public API

struct UserProxy *user_proxy_new(void) {
    struct IProxy *super = puremvc_proxy_new(UserProxy_NAME, collection_array_new());
    if (super == NULL) return NULL;

    struct UserProxy *proxy = init(alloc());
    if (proxy == NULL) {
        puremvc_proxy_dealloc(&super);
        return NULL;
    }

    super->on_register = on_register;
    super->on_remove = on_remove;

    // wire bidirectional references
    super->sub = proxy; // interface to subclass
    proxy->super = super; // subclass to interface

    return proxy;
}

void user_proxy_dealloc(struct UserProxy **proxy) {
    if (proxy == NULL || *proxy == NULL) return;

    struct IProxy *super = (*proxy)->super;
    struct IArray *data = super->get_data(super);
    collection_array_dealloc(&data, free);

    puremvc_proxy_dealloc(&super); // Destroy super.

    free(*proxy); // Destroy sub.
    *proxy = NULL;
}

#pragma endregion
