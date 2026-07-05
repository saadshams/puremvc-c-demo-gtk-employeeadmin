#pragma once

#pragma region Types

struct IUserForm {
    void *context;
    void (*on_update)(void *context, void *data);
};

#pragma endregion
