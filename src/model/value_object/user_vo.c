#include "user_vo.h"

#pragma region Accessors

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

#pragma endregion

#pragma region Operations

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

static const char *given_name(const struct UserVO *self, char *buffer, size_t buffer_size) {
    if (self == NULL || buffer == NULL || buffer_size == 0) return NULL;

    snprintf(buffer, buffer_size, "%s, %s", self->last, self->first);
    return buffer;
}

#pragma endregion

#pragma region GObject Wrapper

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

#pragma endregion

#pragma region Memory Management

static size_t size(void) {
    return (sizeof(struct UserVO) + (sizeof(void *) - 1u)) & ~(sizeof(void *) - 1u);
}

static struct UserVO *alloc(void) {
    struct UserVO *user_vo = malloc(size());

    if (user_vo == NULL) {
        fprintf(stderr, "\033[0;31m[EmployeeAdmin::UserVO::alloc] ERROR: Instance allocation failed.\033[0m\n");
        return NULL;
    }

    return user_vo;
}

static struct UserVO *init(struct UserVO *user_vo, const char *username, const char *first, const char *last, const char *email, const char *password, const enum DeptEnum department) {
    if (user_vo == NULL) return NULL;

    struct UserVO *this = user_vo;
    memset(this, 0, size());

    this->username = strdup(username != NULL ? username : "");
    if (this->username == NULL) goto exception;

    this->first = strdup(first != NULL ? first : "");
    if (this->first == NULL) goto exception;

    this->last = strdup(last != NULL ? last : "");
    if (this->last == NULL) goto exception;

    this->email = strdup(email != NULL ? email : "");
    if (this->email == NULL) goto exception;

    this->password = strdup(password != NULL ? password : "");
    if (this->password == NULL) goto exception;

    this->department = department;

    this->validate = validate;
    this->given_name = given_name;

    return this;

exception:
    user_vo_dealloc(&this);
    return NULL;
}

#pragma endregion

#pragma region Public API

struct UserVO *user_vo_new(const char *username, const char *first, const char *last, const char *email, const char *password, const enum DeptEnum department) {
    return init(alloc(), username, first, last, email, password, department);
}

void user_vo_dealloc(struct UserVO **user_vo) {
    if (user_vo == NULL || *user_vo == NULL) return;
    const struct UserVO *this = *user_vo;

    free(this->username);
    free(this->first);
    free(this->last);
    free(this->email);
    free(this->password);

    free(*user_vo);
    *user_vo = NULL;
}

#pragma endregion
