#pragma once

#include <stddef.h>

#include "model/enum/role_enum.h"

#define MAX_ROLES 16

struct RoleVO {
    const char *username;
    enum RoleEnum roles[MAX_ROLES];
    size_t count; // number of roles stored
};

void role_vo_init(struct RoleVO *role_vo, const char *username, const enum RoleEnum *roles, size_t count);
