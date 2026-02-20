#pragma once

#include <puremvc/puremvc.h>

#define RoleProxy_NAME "RoleProxy"

struct RoleProxy {
    struct IProxy *super;
};

struct IProxy *role_proxy_init(void *buffer, const char *name, void *data);
