#pragma once

#include "employee_admin/i_user_role.h"

#include <gtk/gtk.h>

GtkWidget *user_role_init();

void user_role_set_delegate(struct IUserRole _delegate);
