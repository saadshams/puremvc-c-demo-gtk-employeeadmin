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

    bool (*is_valid)(const struct UserVO *self, const char *password);
    bool (*validate)(GtkWidget *username, GtkWidget *password, GtkWidget *confirm, GtkWidget *department);
    const char *(*given_name)(const struct UserVO *self, char *buffer, size_t buffer_size);
};

typedef struct UserVOObject {
    GObject parent_instance;
    struct UserVO *user;
} UserVOObject;

typedef struct UserVOObjectClass {
    GObjectClass parent_class;
} UserVOObjectClass;

GType user_vo_object_get_type(void);
UserVOObject *user_vo_object_new(struct UserVO *user);

const char *user_vo_get_username(const struct UserVO *self);
const char *user_vo_get_first(const struct UserVO *self);
const char *user_vo_get_last(const struct UserVO *self);
const char *user_vo_get_email(const struct UserVO *self);
const char *user_vo_get_password(const struct UserVO *self);
const char *user_vo_get_department(const struct UserVO *self);

struct UserVO *user_vo_new(const char *username, const char *first, const char *last, const char *email, const char *password, enum DeptEnum department);

void user_vo_dealloc(struct UserVO **user_vo);
