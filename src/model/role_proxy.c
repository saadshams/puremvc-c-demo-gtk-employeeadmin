#include "role_proxy.h"

#include <string.h>
#include <collection/i_array.h>

#pragma region Operations

static struct IArray *find_all(const struct RoleProxy *self) {
    const struct IProxy *super = self->super;
    return super->get_data(super);
}

static void add_item(const struct RoleProxy *self, struct RoleVO *role) {
    const struct IProxy *super = self->super;
    struct IArray *roles = super->get_data(super);

    roles->push(roles, role);
}

static void add_role_to_user(const struct RoleProxy *self, const struct UserVO *user, const enum RoleEnum role) {
    const struct IProxy *super = self->super;
    const struct IArray *role_vos = super->get_data(super);

    for (size_t i = 0, size = role_vos->count(role_vos); i < size; i++) {
        const struct RoleVO *role_vo = role_vos->get(role_vos, i);

        if (strcmp(role_vo->username, user->username) != 0)
            continue;

        const struct IArray *roles = role_vo->roles;
        for (size_t j = 0; j < roles->count(roles); ++j) { // existing
            const enum RoleEnum *stored = roles->get(roles, j);
            if (*stored == role) return;
        }

        enum RoleEnum *value = malloc(sizeof(enum RoleEnum)); // save
        if (!value) {
            fprintf(stderr, "\033[0;31m[EmployeeAdmin::RoleEnum::alloc] ERROR: Instance allocation failed.\033[0m\n");
            return;
        }

        *value = role;
        role_vo->roles->push(role_vo->roles, value);

        break;
    }
}

static void remove_role_from_user(const struct RoleProxy *self, const struct UserVO *user, const enum RoleEnum role) {
    const struct IProxy *super = self->super;
    const struct IArray *role_vos = super->get_data(super);

    for (size_t i = 0, count = role_vos->count(role_vos); i < count; i++) {
        const struct RoleVO *role_vo = role_vos->get(role_vos, i);

        if (strcmp(role_vo->username, user->username) != 0)
            continue;

        struct IArray *roles = role_vo->roles;

        for (size_t j = 0; j < roles->count(roles); j++) { // existing
            const enum RoleEnum *stored = roles->get(roles, j);
            if (*stored == role) {
                roles->remove_item(roles, stored);
                free((void *) stored);
                return;
            }
        }

        break;
    }
}

#pragma endregion

#pragma region Memory Management

static size_t size(void) {
    return (sizeof(struct RoleProxy) + (sizeof(void *) - 1u)) & ~(sizeof(void *) - 1u);
}

static struct RoleProxy *alloc(void) {
    struct RoleProxy *proxy = malloc(size());

    if (proxy == NULL) {
        fprintf(stderr, "\033[0;31m[EmployeeAdmin::RoleProxy::alloc] ERROR: Instance allocation failed.\033[0m\n");
        return NULL;
    }

    return proxy;
}

static struct RoleProxy *init(struct RoleProxy *proxy) {
    if (proxy == NULL) return NULL;

    memset(proxy, 0, size());

    proxy->find_all = find_all;
    proxy->add_item = add_item;
    proxy->add_role_to_user = add_role_to_user;
    proxy->remove_role_from_user = remove_role_from_user;

    return proxy;
}

#pragma endregion

#pragma region Public API

struct IProxy *role_proxy_new(void) {
    struct IArray *data = collection_array_new();
    if (data == NULL) return NULL;

    struct IProxy *super = puremvc_proxy_new(RoleProxy_NAME, data);
    if (super == NULL) {
        collection_array_dealloc(&data, NULL);
        return NULL;
    }

    struct RoleProxy *proxy = init(alloc());
    if (proxy == NULL) {
        collection_array_dealloc(&data, NULL);
        puremvc_proxy_dealloc(&super);
        return NULL;
    }

    // wire bidirectional references
    super->sub = proxy; // interface to subclass
    proxy->super = super; // subclass to interface

    return super;
}

void role_proxy_dealloc(struct RoleProxy **proxy) {
    if (proxy == NULL || *proxy == NULL) return;

    struct IProxy *super = (*proxy)->super;
    struct IArray *data = super->get_data(super);
    collection_array_dealloc(&data, free);

    puremvc_proxy_dealloc(&super); // Destroy super.

    free(*proxy); // Destroy sub.
    *proxy = NULL;
}

#pragma endregion
