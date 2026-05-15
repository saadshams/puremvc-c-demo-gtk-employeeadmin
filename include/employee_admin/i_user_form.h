#pragma once

struct IUserForm {
    void *context;
    void (*callback)(void *context, void *data);
    void (*on_update)(void *context, void *data);
};
