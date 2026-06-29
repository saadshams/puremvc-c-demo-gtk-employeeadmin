#pragma once

struct IUserForm {
    void *context;
    void (*on_update)(void *context, void *data);
};
