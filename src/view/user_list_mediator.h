#pragma once

#include <puremvc/puremvc.h>

#define UserListMediator_NAME "UserListMediator"

struct UserListMediator {
    struct IMediator *super;
};

struct IMediator *user_list_mediator_init(void *buffer, const char *name, void *component);

struct UserListMediator *user_list_mediator_bind(struct UserListMediator *mediator, struct IMediator *super);
