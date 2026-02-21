#pragma once

#include "model/valueObject/user_vo.h"
#include "model/enum/role_enum.h"

#include <puremvc/puremvc.h>

#define RoleProxy_NAME "RoleProxy"

struct RoleProxy {
    struct IProxy *super;

    void (*addRoleToUser)(const struct RoleProxy *self, const struct UserVO *user, enum RoleEnum role);
    void (*removeRoleFromUser)(const struct RoleProxy *self, const struct UserVO *user, enum RoleEnum role);
};

struct IProxy *role_proxy_init(void *buffer, const char *name, void *data);

struct RoleProxy *role_proxy_bind(struct RoleProxy *proxy, struct IProxy *super);
