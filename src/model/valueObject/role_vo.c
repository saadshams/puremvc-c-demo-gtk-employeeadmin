#include "role_vo.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Memory Management

static size_t size(void) {
    return (sizeof(struct RoleVO) + (sizeof(void *) - 1u)) & ~(sizeof(void *) - 1u);
}

static struct RoleVO *alloc(void) {
    struct RoleVO *role_vo = malloc(size());

    if (role_vo == NULL) {
        fprintf(stderr, "\033[0;31m[EmployeeAdmin::RoleVO::alloc] ERROR: Instance allocation failed.\033[0m\n");
        return NULL;
    }

    return role_vo;
}

static struct RoleVO *init(struct RoleVO *role_vo, char *username) {
    if (role_vo == NULL) return NULL;

    struct RoleVO *this = role_vo;
    memset(this, 0, size());

    this->username = strdup(username);
    if (this->username == NULL) goto exception;

    if ((this->roles = collection_array_new()) == NULL) goto exception;

    // for (size_t i = 0; roles[i] != ROLE_NONE_SELECTED; i++) {
    //     enum RoleEnum *role = malloc(sizeof(enum RoleEnum));
    //     if (!role) goto exception;
    //
    //     *role = roles[i];
    //     this->roles->push(this->roles, role);
    // }

    return this;

exception:
    role_vo_dealloc(&this);
    return NULL;
}

#pragma endregion

#pragma region Public API

struct RoleVO *role_vo_new(char *username) {
    return init(alloc(), username);
}

void role_vo_dealloc(struct RoleVO **role_vo) {
    if (role_vo == NULL || *role_vo == NULL) return;
    struct RoleVO *this = *role_vo;

    free(this->username);
    collection_array_dealloc(&this->roles, free);

    free(*role_vo);
    *role_vo = NULL;
}

#pragma endregion
