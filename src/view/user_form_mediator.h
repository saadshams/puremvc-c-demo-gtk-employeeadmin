#pragma once

#include "model/value_object/user_vo.h"

#include <puremvc/puremvc.h>

#define UserFormMediator_NAME "UserFormMediator"

struct UserFormMediator {
    struct IMediator *super;

    void (*set_component)(const struct UserFormMediator *mediator, void *component);
    void (*on_update)(const struct IMediator *self, UserVOObject *user);
};

struct IMediator *user_form_mediator_new(void);

void user_form_mediator_dealloc(struct UserFormMediator **mediator);
