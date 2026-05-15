#pragma once

#include "model/valueObject/user_vo.h"

#include <stddef.h>

struct IUserList {
    void *context;
    size_t (*get_user_list)(void *context, struct UserVO **out, size_t max);
    void (*on_new)(void *context, const struct UserVO *user);
    void (*on_delete)(void *context, const struct UserVO *user);
    void (*on_select)(void *context, const struct UserVO *user);
};
