#pragma once

#include "model/valueObject/user_vo.h"

#include <puremvc/puremvc.h>

#define UserProxy_NAME "UserProxy"

struct UserProxy {
    struct IProxy *super;

    struct IArray *(*find_all)(const struct UserProxy *self);
    bool (*save)(const struct UserProxy *self, const struct UserVO *user);
    bool (*update)(const struct UserProxy *self, const struct UserVO *user);
    bool (*delete)(const struct UserProxy *self, const struct UserVO *user);
};

struct IProxy *user_proxy_new(void);

void user_proxy_dealloc(struct UserProxy **proxy);
