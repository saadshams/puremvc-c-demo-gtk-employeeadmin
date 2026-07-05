#pragma once

#include "employee_admin/i_user_list.h"
#include "model/value_object/user_vo.h"

#include "gtk/gtk.h"

GtkWidget *user_list_init(GtkWidget *window);

void user_list_run();

void user_list_refresh(const struct UserVO *user);

void user_list_set_delegate(struct IUserList _delegate);
