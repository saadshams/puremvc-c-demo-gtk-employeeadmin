#pragma once

#include <puremvc/puremvc.h>

#define UserRoleMediator_NAME "UserRoleMediator"

struct UserRoleMediator {
    struct IMediator *super;

    void (*registerComponent)(const struct UserRoleMediator *mediator, void *component);
};

struct IMediator *user_role_mediator_init(void *buffer, const char *name, void *component);

struct UserRoleMediator *user_role_mediator_bind(struct UserRoleMediator *mediator, struct IMediator *super);
