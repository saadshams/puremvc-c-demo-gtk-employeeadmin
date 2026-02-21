#include "role_proxy.h"

#include "model/valueObject/role_vo.h"

#include <string.h>

static void addRoleToUser(const struct RoleProxy *self, const struct UserVO *user, const enum RoleEnum role) {
    const struct IProxy *this = self->super;
    struct RoleVO **data = this->getData(this);

    for (size_t i = 0; data[i] != NULL; i++) {
        if (strcmp(data[i]->username, user->username) == 0) {

            for (size_t j = 0; j < MAX_ROLES; j++) { // existing
                if (data[i]->roles[j] == role) return;
            }

            for (size_t j = 0; j < MAX_ROLES - 1; j++) { // keep terminator
                if (data[i]->roles[j] == ROLE_NONE_SELECTED) {
                    data[i]->roles[j] = role;
                    return;
                }
            }
        }
    }
}

static void removeRoleFromUser(const struct RoleProxy *self, const struct UserVO *user, const enum RoleEnum role) {
    const struct IProxy *this = self->super;
    struct RoleVO **data = this->getData(this);

    for (size_t i = 0; data[i] != NULL; i++) {
        if (strcmp(data[i]->username, user->username) == 0) {
            size_t index = 0;
            for (size_t j = 0; j < MAX_ROLES && data[i]->roles[j] != ROLE_NONE_SELECTED; j++) {
                if (data[i]->roles[j] == role) {

                } else {
                    if (index != j)
                        data[i]->roles[index] = data[i]->roles[j]; // shift left
                    index++;
                }
            }
            data[i]->roles[index] = ROLE_NONE_SELECTED;
            break;
        }
    }
}

struct IProxy *role_proxy_init(void *buffer, const char *name, void *data) {
    struct IProxy *proxy = puremvc_proxy_init(buffer, name, data);
    return proxy;
}

struct RoleProxy *role_proxy_bind(struct RoleProxy *proxy, struct IProxy *super) {
    proxy->super = super;

    proxy->addRoleToUser = addRoleToUser;
    proxy->removeRoleFromUser = removeRoleFromUser;

    return proxy;
}
