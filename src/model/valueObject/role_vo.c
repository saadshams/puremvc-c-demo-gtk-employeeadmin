#include "role_vo.h"

#include <string.h>

void role_vo_init(struct RoleVO *role_vo, const char *username, const enum RoleEnum *roles, size_t count) {
    if (role_vo == NULL) return;

    memset(role_vo->roles, NONE_SELECTED, sizeof(*role_vo));
    role_vo->count = 0;

    if (roles != NULL && count > 0) {
        size_t n = count < MAX_ROLES ? count : MAX_ROLES;
        for (size_t i = 0; i < n; i++) {
            role_vo->roles[i] = roles[i];
        }
        role_vo->count = n;
    }

}

/**
 *
*struct RoleVO user_roles;

enum RoleEnum my_roles[] = { ROLE_ADMIN, ROLE_PAYROLL, ROLE_INVENTORY };

RoleVO_init(&user_roles, "jsmith", my_roles, 3);

printf("Username: %s\n", user_roles.username);
printf("Roles: ");
for (size_t i = 0; i < user_roles.role_count; i++) {
printf("%d ", user_roles.roles[i]);
}
printf("\n");

*/