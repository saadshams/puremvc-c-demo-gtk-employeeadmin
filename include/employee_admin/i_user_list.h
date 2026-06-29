#pragma once

#include <collection/i_array.h>

struct IUserList {
    void *context;
    struct IArray *(*find_all)(void *context);
    void (*on_new)(void *context, const void *data);
    void (*on_delete)(void *context, const void *data);
    void (*on_select)(void *context, const void *data);
};
