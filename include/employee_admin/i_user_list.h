#pragma once

struct IUserList {
    void *context;
    void (*getUsers)(void *context);
};
