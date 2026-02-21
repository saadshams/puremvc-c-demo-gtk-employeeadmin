#pragma once

#include "employee_admin/i_user_list.h"

#include "gtk/gtk.h"

GtkWidget *user_list_init();

void user_list_start();

void user_list_set_delegate(struct IUserList _delegate);
