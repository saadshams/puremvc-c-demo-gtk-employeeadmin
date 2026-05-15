#pragma once

#include "model/valueObject/user_vo.h"

#include <puremvc/puremvc.h>

#define UserListMediator_NAME "UserListMediator"

struct UserListMediator {
    struct IMediator *super;

    void (*registerComponent)(const struct UserListMediator *mediator, void *component);

    size_t (*get_user_list)(const struct IMediator *self, struct UserVO **out, size_t max);
    void (*on_new)(const struct IMediator *self, const struct UserVO *user);
    void (*on_delete)(const struct IMediator *self, struct UserVO *user);
    void (*on_select)(const struct IMediator *self, struct UserVO *user);
};

struct IMediator *user_list_mediator_init(void *buffer, const char *name, void *component);

struct UserListMediator *user_list_mediator_bind(struct UserListMediator *mediator, struct IMediator *super);
