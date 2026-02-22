#pragma once

#include "model/valueObject/user_vo.h"

#include <stddef.h>

struct IUserList {
    void *context;
    size_t (*list)(void *context, struct UserVO **out, size_t max);
};
