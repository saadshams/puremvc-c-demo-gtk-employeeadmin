#pragma once

#include "view/components/user_list.h"
#include "view/components/user_form.h"
#include "view/components/user_role.h"

#include <gtk/gtk.h>

struct Stage {
    struct UserList list;
    struct UserForm form;
    struct UserRole role;
};

GtkApplication *getApp(struct Stage *stage);
