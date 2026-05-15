#pragma once

#include "model/enum/dept_enum.h"

#include <stdbool.h>
#include <gtk/gtk.h>

#define MAX_USERS 64

struct UserVO {
    char *username;
    char *first;
    char *last;
    char *email;
    char *password;
    enum DeptEnum department;

    bool (*isValid)(const struct UserVO *self, const char *password);
    const char *(*givenName)(const struct UserVO *self, char *buffer, size_t buffer_size);
};

typedef struct {
    GObject parent_instance;
    struct UserVO *user;
} UserVOObject;

typedef struct {
    GObjectClass parent_class;
} UserVOObjectClass;

GType user_vo_object_get_type(void);
UserVOObject *user_vo_object_new(struct UserVO *user);

const char *user_vo_get_username(const struct UserVO *self);
const char *user_vo_get_first(const struct UserVO *self);
const char *user_vo_get_last(const struct UserVO *self);
const char *user_vo_get_email(const struct UserVO *self);
const char *user_vo_get_department(const struct UserVO *self);

void user_vo_init(struct UserVO *self, char *username, char *first, char *last, char *email, char *password, enum DeptEnum department);
