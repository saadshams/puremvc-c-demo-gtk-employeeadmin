#pragma once

#include "model/enum/role_enum.h"

#define MAX_ROLES 15

struct RoleVO {
    const char *username;
    enum RoleEnum roles[MAX_ROLES];
};

void role_vo_init(struct RoleVO *self, const char *username, const enum RoleEnum *roles);
