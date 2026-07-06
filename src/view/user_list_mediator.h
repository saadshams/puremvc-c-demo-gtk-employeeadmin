#pragma once

#include "model/value_object/user_vo.h"

#include <puremvc/puremvc.h>

#define UserListMediator_NAME "UserListMediator"

struct UserListMediator {
    struct IMediator *super;

    void (*set_component)(const struct UserListMediator *mediator, void *component);

    GListStore *(*find_all)(const struct IMediator *self);
    void (*on_new)(const struct IMediator *self, const UserVOObject *object);
    void (*on_delete)(const struct IMediator *self, UserVOObject *object);
    void (*on_select)(const struct IMediator *self, UserVOObject *object);
};

struct IMediator *user_list_mediator_new(void);

void user_list_mediator_dealloc(struct UserListMediator **mediator);
