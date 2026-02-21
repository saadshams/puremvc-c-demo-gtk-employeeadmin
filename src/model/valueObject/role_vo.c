#include "role_vo.h"

#include <stddef.h>

void role_vo_init(struct RoleVO *self, const char *username, const enum RoleEnum roles[]) {
    self->username = username;
    for (size_t i = 0U; i < MAX_ROLES; ++i) {
        if (roles != NULL) {
            self->roles[i] = roles[i];
        } else {
            self->roles[i] = ROLE_NONE_SELECTED;
        }
    }
}
