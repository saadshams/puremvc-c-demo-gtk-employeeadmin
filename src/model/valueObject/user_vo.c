#include <stdio.h>

#include "user_vo.h"

void user_vo_init(struct UserVO *user_vo, const char *username, const char *first_name, const char *last_name, const char *email, const char *password, const enum DeptEnum department) {
    if (user_vo == NULL) return;
    user_vo->username = username != NULL ? username : "";
    user_vo->first_name = first_name != NULL ? first_name : "";
    user_vo->last_name = last_name != NULL ? last_name : "";
    user_vo->email = email != NULL ? email : "";
    user_vo->password = password != NULL ? password : "";
    user_vo->department = department;
}

bool user_vo_is_valid(const struct UserVO *user_vo, const char *password) {
    if (user_vo == NULL) return false;
    return user_vo->username != NULL && user_vo->password != password && user_vo->department != NONE_SELECTED;
}

const char *user_vo_get_given_name(const struct UserVO *user_vo, char *buffer, size_t buffer_size) {
    if (user_vo == NULL || buffer == NULL || buffer_size == 0) return NULL;

    snprintf(buffer, buffer_size, "%s, %s", user_vo->last_name, user_vo->first_name);
    return buffer;
}

/*
*    struct UserVO user;

    UserVO_init(&user,
                "jsmith",
                "John",
                "Smith",
                "jsmith@example.com",
                "12345",
                ACCT);

    printf("Is valid? %s\n", UserVO_isValid(&user) ? "Yes" : "No");

    char buf[256];
    printf("Given name: %s\n", UserVO_getGivenName(&user, buf, sizeof(buf)));

 */