#pragma once

#include "model/value_object/user_vo.h"

#include <puremvc/puremvc.h>

#define UserProxy_NAME "UserProxy"

struct UserProxy {
    struct IProxy *super;

    GListStore *(*find_all)(const struct UserProxy *self);
    bool (*save)(const struct UserProxy *self, UserVOObject *user);
    bool (*update)(const struct UserProxy *self, UserVOObject *user);
    bool (*delete)(const struct UserProxy *self, const UserVOObject *user);
};

struct IProxy *user_proxy_new(void);

void user_proxy_dealloc(struct UserProxy **proxy);
