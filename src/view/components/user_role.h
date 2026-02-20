#pragma once

#include "employee_admin/i_user_role.h"

#include <gtk/gtk.h>

struct UserRole {
    GtkWidget *widget;

    struct IUserRole delegate;
    void (*setDelegate)(struct UserRole *self, struct IUserRole delegate);
};

GtkWidget *user_role_init();
