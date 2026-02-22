#pragma once

#include "model/valueObject/user_vo.h"

#include <puremvc/puremvc.h>

#define UserListMediator_NAME "UserListMediator"

struct UserListMediator {
    struct IMediator *super;

    size_t (*list)(const struct UserListMediator *self, struct UserVO **out, size_t max);
    void (*registerComponent)(const struct UserListMediator *mediator, void *component);
};

struct IMediator *user_list_mediator_init(void *buffer, const char *name, void *component);

struct UserListMediator *user_list_mediator_bind(struct UserListMediator *mediator, struct IMediator *super);
