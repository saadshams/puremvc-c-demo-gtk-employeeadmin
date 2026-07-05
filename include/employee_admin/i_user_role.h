#pragma once

#pragma region Types

struct IUserRole {
    void *context;
    void (*callback)(void *context, void *data);
};

#pragma endregion
