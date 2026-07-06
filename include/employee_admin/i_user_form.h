#pragma once

#pragma region Types

#include "model/value_object/user_vo.h"

struct IUserForm {
    void *context;
    void (*on_update)(void *context, UserVOObject *data);
};

#pragma endregion
