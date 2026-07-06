#pragma once

#include "model/value_object/user_vo.h"

#include <gtk/gtk.h>

#pragma region Types

struct IUserList {
    void *context;
    GListStore *(*find_all)(void *context);
    void (*on_new)(void *context, const UserVOObject *object);
    void (*on_delete)(void *context, const UserVOObject *object);
    void (*on_select)(void *context, const UserVOObject *object);
};

#pragma endregion
