#pragma once

#include <puremvc/puremvc.h>

#define UserFormMediator_NAME "UserFormMediator"

struct UserFormMediator {
    struct IMediator *super;
};

struct IMediator *user_form_mediator_init(void *buffer, const char *name, void *component);

struct UserFormMediator *user_form_mediator_bind(struct UserFormMediator *mediator, struct IMediator *super);
