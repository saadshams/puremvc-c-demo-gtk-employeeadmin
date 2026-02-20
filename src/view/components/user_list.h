#pragma once

#include "employee_admin/i_user_list.h"

#include "gtk/gtk.h"

struct UserList {
    GtkWidget *widget;

    struct IUserList delegate;
    void (*setDelegate)(struct UserList *self, struct IUserList delegate);
};

GtkWidget *user_list_init();
