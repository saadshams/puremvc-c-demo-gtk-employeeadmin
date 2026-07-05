#pragma once

#include "model/value_object/user_vo.h"
#include "model/value_object/role_vo.h"
#include "model/enum/role_enum.h"

#include <puremvc/puremvc.h>

#define RoleProxy_NAME "RoleProxy"

struct RoleProxy {
    struct IProxy *super;

    struct IArray *(*find_all)(const struct RoleProxy *self);
    void (*add_item)(const struct RoleProxy *self, struct RoleVO *role);
    void (*add_role_to_user)(const struct RoleProxy *self, const struct UserVO *user, enum RoleEnum role);
    void (*remove_role_from_user)(const struct RoleProxy *self, const struct UserVO *user, enum RoleEnum role);
};

struct IProxy *role_proxy_new();

void role_proxy_dealloc(struct RoleProxy **proxy);
