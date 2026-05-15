#pragma once

#include <stddef.h>

struct IUserList {
    void *context;
    size_t (*get_users)(void *context, void *data, size_t max);
    void (*on_new)(void *context, const void *data);
    void (*on_delete)(void *context, const void *data);
    void (*on_select)(void *context, const void *data);
};
