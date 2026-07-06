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

static GListStore *find_all(const struct UserProxy *self) {
    const struct IProxy *super = self->super;
    return super->get_data(super);;
}

static bool save(const struct UserProxy *self, UserVOObject *user) {
    const struct IProxy *super = self->super;
    GListStore *store = super->get_data(super);

    const guint count = g_list_model_get_n_items(G_LIST_MODEL(store));
    for (guint i = 0; i < count; i++) {
        UserVOObject *current = g_list_model_get_item(G_LIST_MODEL(store), i);
        const bool found = strcmp(current->user->username, user->user->username) == 0;
        g_object_unref(current);

        if (found) return false;
    }

    g_list_store_append(store, user);

    return true;
}

static bool update(const struct UserProxy *self, UserVOObject *user) {
    const struct IProxy *super = self->super;
    GListStore *store = super->get_data(super);

    const guint count = g_list_model_get_n_items(G_LIST_MODEL(store));
    for (guint i = 0; i < count; i++) {
        UserVOObject *current = g_list_model_get_item(G_LIST_MODEL(store), i);
        const bool found = strcmp(current->user->username, user->user->username) == 0;
        g_object_unref(current);

        if (found) {
            g_list_store_splice(store, i, 1, (gpointer *) &user, 1);
            return true;
        }
    }

    return false;
}

static bool delete(const struct UserProxy *self, const UserVOObject *user) {
    const struct IProxy *super = self->super;
    GListStore *store = super->get_data(super);

    const guint count = g_list_model_get_n_items(G_LIST_MODEL(store));
    for (guint i = 0; i < count; i++) {
        UserVOObject *current = g_list_model_get_item(G_LIST_MODEL(store), i);
        const bool found = strcmp(current->user->username, user->user->username) == 0;
        g_object_unref(current);

        if (found) {
            g_list_store_remove(store, i);
            return true;
        }
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

struct IProxy *user_proxy_new(void) {
    GListStore *store = g_list_store_new(user_vo_object_get_type());
    if (store == NULL) return NULL;

    struct IProxy *super = puremvc_proxy_new(UserProxy_NAME, store);
    if (super == NULL) {
        g_object_unref(store);
        return NULL;
    }

    struct UserProxy *proxy = init(alloc());
    if (proxy == NULL) {
        g_object_unref(store);
        puremvc_proxy_dealloc(&super);
        return NULL;
    }

    super->on_register = on_register;
    super->on_remove = on_remove;

    // wire bidirectional references
    super->sub = proxy; // interface to subclass
    proxy->super = super; // subclass to interface

    return super;
}

void user_proxy_dealloc(struct UserProxy **proxy) {
    if (proxy == NULL || *proxy == NULL) return;

    struct IProxy *super = (*proxy)->super;
    GListStore *store = super->get_data(super);
    g_object_unref(store);

    puremvc_proxy_dealloc(&super); // Destroy super.

    free(*proxy); // Destroy sub.
    *proxy = NULL;
}

#pragma endregion
