#pragma once

struct IUserList {
    void *context;
    void (*callback)(void *context, void *data);
};
