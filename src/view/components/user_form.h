#pragma once

#include "employee_admin/i_user_form.h"

#include "gtk/gtk.h"

GtkWidget *user_form_init();

void user_form_set_delegate(struct IUserForm _delegate);
