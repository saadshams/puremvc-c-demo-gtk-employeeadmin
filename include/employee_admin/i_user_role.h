#pragma once

struct IUserRole {
    void *context;
    void (*callback)(void *context, void *data);
};
