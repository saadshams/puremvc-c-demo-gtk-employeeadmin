#pragma once

#include "employee_admin/i_user_form.h"
#include "model/valueObject/user_vo.h"

#include "gtk/gtk.h"

GtkWidget *user_form_init(GtkWidget *window);

void user_form_reset(void);

void user_form_set_user(struct UserVO *user);

void user_form_set_delegate(struct IUserForm _delegate);
