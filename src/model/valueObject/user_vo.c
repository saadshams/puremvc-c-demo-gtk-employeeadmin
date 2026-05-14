#include "user_vo.h"

static bool isValid(const struct UserVO *self, const char *password) {
    if (self == NULL) return false;

    return self->username != NULL && self->password != NULL && strcmp(self->password, password) == 0
        && self->department != DEPT_NONE_SELECTED;
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

G_DEFINE_TYPE(UserObject, user_object, G_TYPE_OBJECT)

static void user_object_class_init(UserObjectClass *klass) {}

static void user_object_init(UserObject *self) {
    self->user = NULL;
}

UserObject *user_object_new(struct UserVO *user) {
    UserObject *object = g_object_new(user_object_get_type(), NULL);
    object->user = user;
    return object;
}
