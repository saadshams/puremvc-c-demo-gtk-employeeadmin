#pragma once

#include <stdbool.h>

#include "model/enum/dept_enum.h"

struct UserVO {
    const char *username;
    const char *first_name;
    const char *last_name;
    const char *email;
    const char *password;
    enum DeptEnum department;
};

void user_vo_init(struct UserVO *user_vo, const char *username, const char *first_name, const char *last_name, const char *email, const char *password, enum DeptEnum department);

bool user_vo_is_valid(const struct UserVO *user_vo, const char *password);

const char *user_vo_get_given_name(const struct UserVO *user_vo, char *buffer, size_t buffer_size);
