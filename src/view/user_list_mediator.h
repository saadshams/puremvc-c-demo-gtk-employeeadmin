#pragma once

#include "model/valueObject/user_vo.h"

#include <puremvc/puremvc.h>
#include <collection/i_array.h>

#define UserListMediator_NAME "UserListMediator"

struct UserListMediator {
    struct IMediator *super;

    void (*set_component)(const struct UserListMediator *mediator, void *component);

    struct IArray *(*find_all)(const struct IMediator *self);
    void (*on_new)(const struct IMediator *self, const struct UserVO *user);
    void (*on_delete)(const struct IMediator *self, struct UserVO *user);
    void (*on_select)(const struct IMediator *self, struct UserVO *user);
};

struct IMediator *user_list_mediator_new();

struct UserListMediator *user_list_mediator_extend(struct UserListMediator *mediator, struct IMediator *super);
