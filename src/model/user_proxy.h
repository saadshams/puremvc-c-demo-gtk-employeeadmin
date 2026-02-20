#pragma once

#include <puremvc/puremvc.h>

#define UserProxy_NAME "UserProxy"

struct UserProxy {
    struct IProxy *super;
};

struct IProxy *user_proxy_init(void *buffer, const char *name, void *data);
