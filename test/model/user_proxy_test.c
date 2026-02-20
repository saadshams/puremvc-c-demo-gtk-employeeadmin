#include "user_proxy_test.h"

#include "model/user_proxy.h"
#include "model/valueObject/user_vo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void beforeAll(void) {}
static void beforeEach(void) {}
static void afterEach(void) {}
static void afterAll(void) {}

static void test(const char *name, void (*callback)(void)) {
    printf("\033[0;34m[RUNNING]\033[0m %s...\n", name);
    fflush(stdout);

    beforeEach();
    callback();
    afterEach();

    printf("\033[0;32m[PASSED]\033[0m %s\n", name);
    fflush(stdout);
}

int main(void) {
    printf("\n\033[1;36m================================================\033[0m\n");
    printf("\033[1;36m[SUITE] %s\033[0m\n", "UserProxyTest");
    printf("\033[1;36m================================================\033[0m\n\n");

    beforeAll();
    test("testCount", testCount);
    test("testIndexOf", testIndexOf);
    test("testList", testList);
    test("testAdd", testAdd);
    test("testUpdate", testUpdate);
    test("testDelete", testDelete);
    afterAll();

    printf("\n\033[1;32m[DONE] All tests in suite finished.\033[0m\n");
    return 0;
}

void testCount(void) {
    struct UserVO users[MAX_USERS] = {0};
    struct IProxy *super = user_proxy_init(alloca(puremvc_proxy_size()), "UserProxyTest", &users);
    const struct UserProxy *proxy = user_proxy_bind(&(struct UserProxy){}, super);

    if (proxy->count(proxy) != 0) abort();

    const struct UserVO larry = { .username = "lstooge", .first = "Larry", .last = "Stooge", .email = "larry@stooges.com", .password = "ijk456", .department = ACCT };
    if (proxy->add(proxy, &larry) == false) abort();
    if (proxy->count(proxy) != 1) abort();

    const struct UserVO curly = { .username = "cstooge", .first = "Curly", .last = "Stooge", .email = "curly@stooges.com", .password = "xyz987", .department = SALES };
    if (proxy->add(proxy, &curly) == false) abort();
    if (proxy->count(proxy) != 2) abort();

    const struct UserVO moe = { .username = "mstooge", .first = "Moe", .last = "Stooge", .email = "moe@stooges.com", .password = "abc123", .department = PLANT };
    if (proxy->add(proxy, &moe) == false) abort();
    if (proxy->count(proxy) != 3) abort();

    if (proxy->add(proxy, &moe) == true) abort(); // duplicate
    if (proxy->count(proxy) != 3) abort();
}

void testIndexOf(void) {
    struct UserVO users[MAX_USERS] = {0};
    struct IProxy *super = user_proxy_init(alloca(puremvc_proxy_size()), "UserProxyTest", &users);
    const struct UserProxy *proxy = user_proxy_bind(&(struct UserProxy){}, super);

    const struct UserVO larry = { .username = "lstooge", .first = "Larry", .last = "Stooge", .email = "larry@stooges.com", .password = "ijk456", .department = ACCT };
    if (proxy->add(proxy, &larry) == false) abort();
    const struct UserVO curly = { .username = "cstooge", .first = "Curly", .last = "Stooge", .email = "curly@stooges.com", .password = "xyz987", .department = SALES };
    if (proxy->add(proxy, &curly) == false) abort();
    const struct UserVO moe = { .username = "mstooge", .first = "Moe", .last = "Stooge", .email = "moe@stooges.com", .password = "abc123", .department = PLANT };
    if (proxy->add(proxy, &moe) == false) abort();

    size_t index = 0;

    if (proxy->indexOf(proxy, "lstooge", &index) != true) abort();
    if (index != 0) abort();

    if (proxy->indexOf(proxy, "cstooge", &index) != true) abort();
    if (index != 1) abort();

    if (proxy->indexOf(proxy, "mstooge", &index) != true) abort();
    if (index != 2) abort();

    if (proxy->indexOf(proxy, "", &index) != false) abort(); // non-existing
    if (index != 2) abort(); // index remains the same from last result

    if (proxy->indexOf(proxy, "sshemp", &index) != false) abort(); // non-existing
    if (index != 2) abort(); // index remains the same from last result

    const struct UserVO shemp = { .username = "sshemp", .first = "Shemp", .last = "Stooge", .email = "shemp@stooges.com", .password = "xyz987", .department = PLANT };
    if (proxy->add(proxy, &shemp) == false) abort();

    if (proxy->indexOf(proxy, "sshemp", &index) != true) abort();
    if (index != 3) abort();
}

void testList(void) {
    struct UserVO users[MAX_USERS] = {0};
    struct IProxy *super = user_proxy_init(alloca(puremvc_proxy_size()), "UserProxyTest", &users);
    const struct UserProxy *proxy = user_proxy_bind(&(struct UserProxy){}, super);

    const struct UserVO larry = { .username = "lstooge", .first = "Larry", .last = "Stooge", .email = "larry@stooges.com", .password = "ijk456", .department = ACCT };
    if (proxy->add(proxy, &larry) == false) abort();
    const struct UserVO curly = { .username = "cstooge", .first = "Curly", .last = "Stooge", .email = "curly@stooges.com", .password = "xyz987", .department = SALES };
    if (proxy->add(proxy, &curly) == false) abort();
    const struct UserVO moe = { .username = "mstooge", .first = "Moe", .last = "Stooge", .email = "moe@stooges.com", .password = "abc123", .department = PLANT };
    if (proxy->add(proxy, &moe) == false) abort();

    struct UserVO *temp[3] = {0};
    proxy->list(proxy, temp, 3);
    for (int i = 0; i < 3; i++) {
        if (strcmp(users[i].username, temp[i]->username) != 0) abort();
    }

    struct UserVO *temp2[4] = {0};
    proxy->list(proxy, temp2, 2); // copy two only
    if (strcmp(temp2[0]->username, users[0].username) != 0) abort();
    if (strcmp(temp2[1]->username, users[1].username) != 0) abort();
    if (temp2[2] != NULL) abort();
    if (temp2[3] != NULL) abort();
}

void testAdd(void) {
    struct UserVO users[MAX_USERS] = {0};
    struct IProxy *super = user_proxy_init(alloca(puremvc_proxy_size()), "UserProxyTest", &users);
    const struct UserProxy *proxy = user_proxy_bind(&(struct UserProxy){}, super);

    const struct UserVO larry = { .username = "lstooge", .first = "Larry", .last = "Stooge", .email = "larry@stooges.com", .password = "ijk456", .department = ACCT };
    if (proxy->add(proxy, &larry) == false) abort();
    const struct UserVO curly = { .username = "cstooge", .first = "Curly", .last = "Stooge", .email = "curly@stooges.com", .password = "xyz987", .department = SALES };
    if (proxy->add(proxy, &curly) == false) abort();

    if (proxy->add(proxy, &larry) == true) abort();
    if (proxy->add(proxy, &curly) == true) abort();

    const struct UserVO moe = { .username = "mstooge", .first = "Moe", .last = "Stooge", .email = "moe@stooges.com", .password = "abc123", .department = PLANT };
    if (proxy->add(proxy, &moe) == false) abort();
    if (proxy->add(proxy, &moe) == true) abort();
}

void testUpdate(void) {
    struct UserVO users[MAX_USERS] = {0};
    struct IProxy *super = user_proxy_init(alloca(puremvc_proxy_size()), "UserProxyTest", &users);
    const struct UserProxy *proxy = user_proxy_bind(&(struct UserProxy){}, super);

    const struct UserVO larry = { .username = "lstooge", .first = "Larry", .last = "Stooge", .email = "larry@stooges.com", .password = "ijk456", .department = ACCT };
    if (proxy->add(proxy, &larry) == false) abort();
    const struct UserVO curly = { .username = "cstooge", .first = "Curly", .last = "Stooge", .email = "curly@stooges.com", .password = "xyz987", .department = SALES };
    if (proxy->add(proxy, &curly) == false) abort();
    const struct UserVO moe = { .username = "mstooge", .first = "Moe", .last = "Stooge", .email = "moe@stooges.com", .password = "abc123", .department = PLANT };
    if (proxy->add(proxy, &moe) == false) abort();

    const struct UserVO updated = { .username = "mstooge", .first = "Moe1", .last = "Stooge1", .email = "moe@stooges.com", .password = "abc123", .department = PLANT };
    if (proxy->update(proxy, &updated) == false) abort();

    if (strcmp(users[2].first, "Moe1") != 0) abort();
    if (strcmp(users[2].last, "Stooge1") != 0) abort();
}

void testDelete(void) {
    struct UserVO users[MAX_USERS] = {0};
    struct IProxy *super = user_proxy_init(alloca(puremvc_proxy_size()), "UserProxyTest", &users);
    const struct UserProxy *proxy = user_proxy_bind(&(struct UserProxy){}, super);

    const struct UserVO larry = { .username = "lstooge", .first = "Larry", .last = "Stooge", .email = "larry@stooges.com", .password = "ijk456", .department = ACCT };
    if (proxy->add(proxy, &larry) == false) abort();
    const struct UserVO curly = { .username = "cstooge", .first = "Curly", .last = "Stooge", .email = "curly@stooges.com", .password = "xyz987", .department = SALES };
    if (proxy->add(proxy, &curly) == false) abort();
    const struct UserVO moe = { .username = "mstooge", .first = "Moe", .last = "Stooge", .email = "moe@stooges.com", .password = "abc123", .department = PLANT };
    if (proxy->add(proxy, &moe) == false) abort();
    const struct UserVO shemp = { .username = "sshemp", .first = "Shemp", .last = "Stooge", .email = "shemp@stooges.com", .password = "xyz987", .department = PLANT };
    if (proxy->add(proxy, &shemp) == false) abort();

    struct UserVO temp = {};
    if (proxy->delete(proxy, &curly, &temp) == false) abort();
    if (strcmp(temp.username, curly.username) != 0) abort();

    if (strcmp(users[0].username, "lstooge") != 0) abort();
    if (strcmp(users[1].username, "mstooge") != 0) abort();
    if (strcmp(users[2].username, "sshemp") != 0) abort();
    if (users[3].username != NULL) abort();

    if (proxy->delete(proxy, &shemp, &temp) == false) abort();
    if (strcmp(temp.username, shemp.username) != 0) abort();
    if (strcmp(users[0].username, "lstooge") != 0) abort();
    if (strcmp(users[1].username, "mstooge") != 0) abort();
    if (users[2].username != NULL) abort();
    if (users[3].username != NULL) abort();

    if (proxy->delete(proxy, &larry, &temp) == false) abort();
    if (strcmp(temp.username, larry.username) != 0) abort();
    if (strcmp(users[0].username, "mstooge") != 0) abort();
    if (users[1].username != NULL) abort();
    if (users[2].username != NULL) abort();
    if (users[3].username != NULL) abort();

    if (proxy->delete(proxy, &moe, &temp) == false) abort();
    if (strcmp(temp.username, moe.username) != 0) abort();
    if (users[0].username != NULL) abort();
    if (users[1].username != NULL) abort();
    if (users[2].username != NULL) abort();
    if (users[3].username != NULL) abort();
}
