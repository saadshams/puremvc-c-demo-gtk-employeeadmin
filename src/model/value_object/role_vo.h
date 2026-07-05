#pragma once

#include "collection/i_array.h"

struct RoleVO {
    char *username;
    struct IArray *roles;
};

struct RoleVO *role_vo_new(char *username);

void role_vo_dealloc(struct RoleVO **role_vo);
