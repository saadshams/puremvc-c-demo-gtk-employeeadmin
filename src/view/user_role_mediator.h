#pragma once

#include <puremvc/puremvc.h>

#define UserRoleMediator_NAME "UserRoleMediator"

struct UserRoleMediator {
    struct IMediator *super;

    void (*set_component)(const struct UserRoleMediator *mediator, void *component);
};

struct IMediator *user_role_mediator_new();

struct UserRoleMediator *user_role_mediator_extend(struct UserRoleMediator *mediator, struct IMediator *super);
