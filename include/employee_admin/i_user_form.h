#pragma once

struct IUserForm {
    void *context;
    void (*callback)(void *context, void *data);
};
