#pragma once

#include "model/valueObject/user_vo.h"

#include <puremvc/puremvc.h>

#define UserFormMediator_NAME "UserFormMediator"

struct UserFormMediator {
    struct IMediator *super;

    void (*set_component)(const struct UserFormMediator *mediator, void *component);
    void (*on_update)(const struct IMediator *self, struct UserVO *user);
};

struct IMediator *user_form_mediator_new();

struct UserFormMediator *user_form_mediator_extend(struct UserFormMediator *mediator, struct IMediator *super);
