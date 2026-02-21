#include <stdio.h>

#include "user_vo.h"

static bool isValid(const struct UserVO *self, const char *password) {
    if (self == NULL) return false;
    return self->username != NULL && self->password != password && self->department != DEPT_NONE_SELECTED;
}

static const char *givenName(const struct UserVO *self, char *buffer, size_t buffer_size) {
    if (self == NULL || buffer == NULL || buffer_size == 0) return NULL;

    snprintf(buffer, buffer_size, "%s, %s", self->last, self->first);
    return buffer;
}

void user_vo_init(struct UserVO *self, const char *username, const char *first, const char *last, const char *email, const char *password, const enum DeptEnum department) {
    self->username = username != NULL ? username : "";
    self->first = first != NULL ? first : "";
    self->last = last != NULL ? last : "";
    self->email = email != NULL ? email : "";
    self->password = password != NULL ? password : "";
    self->department = department;

    self->isValid = isValid;
    self->givenName = givenName;
}
