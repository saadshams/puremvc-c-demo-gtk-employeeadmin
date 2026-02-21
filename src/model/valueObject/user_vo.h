#pragma once

#include "model/enum/dept_enum.h"

#include <stdbool.h>
#include <stddef.h>

#define MAX_USERS 64

struct UserVO {
    const char *username;
    const char *first;
    const char *last;
    const char *email;
    const char *password;
    enum DeptEnum department;

    bool (*isValid)(const struct UserVO *self, const char *password);
    const char *(*givenName)(const struct UserVO *self, char *buffer, size_t buffer_size);
};

void user_vo_init(struct UserVO *self, const char *username, const char *first, const char *last, const char *email, const char *password, enum DeptEnum department);
