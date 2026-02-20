#pragma once

#include "employee_admin/i_user_form.h"

#include "gtk/gtk.h"

struct UserForm {
    GtkWidget *widget;

    struct IUserForm delegate;
    void (*setDelegate)(struct UserForm *self, struct IUserForm delegate);
};

GtkWidget *user_form_init();
