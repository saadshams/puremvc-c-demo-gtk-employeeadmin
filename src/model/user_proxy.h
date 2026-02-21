#pragma once

#include "model/valueObject/user_vo.h"

#include <puremvc/puremvc.h>

#define UserProxy_NAME "UserProxy"

struct UserProxy {
    struct IProxy *super;

    size_t (*count)(const struct UserProxy *self);
    bool (*indexOf)(const struct UserProxy *self, const char *username, size_t *out);
    size_t (*list)(const struct UserProxy *self, struct UserVO **out, size_t max);
    bool (*add)(const struct UserProxy *self, const struct UserVO *user);
    bool (*update)(const struct UserProxy *self, const struct UserVO *user);
    bool (*delete)(const struct UserProxy *self, const struct UserVO *user, struct UserVO *out);
};

struct IProxy *user_proxy_init(void *buffer, const char *name, void *data);

struct UserProxy *user_proxy_bind(struct UserProxy *proxy, struct IProxy *super);
