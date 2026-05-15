#include "user_vo.h"

static bool validate(GtkWidget *username, GtkWidget *password, GtkWidget *confirm, GtkWidget *department) {
    bool isValid = true;
    if (gtk_editable_get_text(GTK_EDITABLE(username))[0] == '\0') {
        isValid = false;
        gtk_widget_add_css_class(username, "error");
    } else {
        gtk_widget_remove_css_class(username, "error");
    }

    if (
        gtk_editable_get_text(GTK_EDITABLE(password))[0] == '\0' ||
        g_strcmp0(
            gtk_editable_get_text(GTK_EDITABLE(password)),
            gtk_editable_get_text(GTK_EDITABLE(confirm))
        ) != 0
    ) {
        isValid = false;
        gtk_widget_add_css_class(password, "error");
        gtk_widget_add_css_class(confirm, "error");
    } else {
        gtk_widget_remove_css_class(password, "error");
        gtk_widget_remove_css_class(confirm, "error");
    }

    if (gtk_drop_down_get_selected(GTK_DROP_DOWN(department)) == 0) {
        isValid = false;
        gtk_widget_add_css_class(department, "error");
    } else {
        gtk_widget_remove_css_class(department, "error");
    }

    return isValid;
}

static const char *givenName(const struct UserVO *self, char *buffer, size_t buffer_size) {
    if (self == NULL || buffer == NULL || buffer_size == 0) return NULL;

    snprintf(buffer, buffer_size, "%s, %s", self->last, self->first);
    return buffer;
}

G_DEFINE_TYPE(UserVOObject, user_vo_object, G_TYPE_OBJECT)

static void user_vo_object_class_init(UserVOObjectClass *klass) {

}

static void user_vo_object_init(UserVOObject *self) {
    self->user = NULL;
}

UserVOObject *user_vo_object_new(const struct UserVO *user) {
    UserVOObject *object = g_object_new(user_vo_object_get_type(), NULL);
    object->user = user;
    return object;
}

const char *user_vo_get_username(const struct UserVO *self) {
    return self ? self->username : "";
}

const char *user_vo_get_first(const struct UserVO *self) {
    return self ? self->first : "";
}

const char *user_vo_get_last(const struct UserVO *self) {
    return self ? self->last : "";
}

const char *user_vo_get_email(const struct UserVO *self) {
    return self ? self->email : "";
}

const char *user_vo_get_department(const struct UserVO *self) {
    return self ? dept_to_string(self->department) : "";
}

struct UserVO *user_vo_init(struct UserVO *self, char *username, char *first, char *last, char *email, char *password, enum DeptEnum department) {
    self->username = username != NULL ? username : "";
    self->first = first != NULL ? first : "";
    self->last = last != NULL ? last : "";
    self->email = email != NULL ? email : "";
    self->password = password != NULL ? password : "";
    self->department = department;

    self->validate = validate;
    self->givenName = givenName;

    return self;
}
