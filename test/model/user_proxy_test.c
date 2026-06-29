#include "user_proxy_test.h"
#include "model/user_proxy.h"
#include "model/valueObject/user_vo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collection/i_array.h"

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
    test("test_find_all", test_find_all);
    test("test_add", test_add);
    test("test_update", test_update);
    test("test_delete", test_delete);
    afterAll();

    printf("\n\033[1;32m[DONE] All tests in suite finished.\033[0m\n");
    return 0;
}

void test_find_all(void) {
    struct IProxy *super = user_proxy_new();
    struct UserProxy *proxy = user_proxy_extend(&(struct UserProxy){}, super);

    struct IArray *users = proxy->find_all(proxy);
    if (users->size(users) != 0) abort();

    const struct UserVO larry = { .username = "lstooge", .first = "Larry", .last = "Stooge", .email = "larry@stooges.com", .password = "ijk456", .department = DEPT_ACCT };
    if (proxy->save(proxy, &larry) == false) abort();
    if (users->size(users) != 1) abort();

    const struct UserVO curly = { .username = "cstooge", .first = "Curly", .last = "Stooge", .email = "curly@stooges.com", .password = "xyz987", .department = DEPT_SALES };
    if (proxy->save(proxy, &curly) == false) abort();
    if (users->size(users) != 2) abort();

    const struct UserVO moe = { .username = "mstooge", .first = "Moe", .last = "Stooge", .email = "moe@stooges.com", .password = "abc123", .department = DEPT_PLANT };
    if (proxy->save(proxy, &moe) == false) abort();
    if (users->size(users) != 3) abort();

    if (proxy->save(proxy, &moe) == true) abort(); // duplicate
    if (users->size(users) != 3) abort();
}

void test_add(void) {
    struct IProxy *super = user_proxy_new();
    struct UserProxy *proxy = user_proxy_extend(&(struct UserProxy){}, super);

    struct IArray *users = proxy->find_all(proxy);
    if (users->size(users) != 0) abort();

    const struct UserVO *larry = user_vo_new("lstooge", "Larry", "Stooge", "larry@stooges.com", "ijk456", DEPT_ACCT);
    if (proxy->save(proxy, larry) == false) abort();

    const struct UserVO *curly = user_vo_new("cstooge", "Curly", "Stooge", "curly@stooges.com", "xyz987", DEPT_SALES);
    if (proxy->save(proxy, curly) == false) abort();

    if (proxy->save(proxy, larry) == true) abort();
    if (proxy->save(proxy, curly) == true) abort();

    const struct UserVO *moe = user_vo_new("mstooge", "Moe", "Stooge", "moe@stooges.com", "abc123", DEPT_PLANT);
    if (proxy->save(proxy, moe) == false) abort();
    if (proxy->save(proxy, moe) == true) abort();
}

void test_update(void) {
    struct IProxy *super = user_proxy_new();
    struct UserProxy *proxy = user_proxy_extend(&(struct UserProxy){}, super);

    struct IArray *users = proxy->find_all(proxy);
    if (users->size(users) != 0) abort();

    const struct UserVO *larry = user_vo_new("lstooge", "Larry", "Stooge", "larry@stooges.com", "ijk456", DEPT_ACCT);
    if (proxy->save(proxy, larry) == false) abort();
    const struct UserVO *curly = user_vo_new("cstooge", "Curly", "Stooge", "curly@stooges.com", "xyz987", DEPT_SALES);
    if (proxy->save(proxy, curly) == false) abort();
    const struct UserVO *moe = user_vo_new("mstooge", "Moe", "Stooge", "moe@stooges.com", "abc123", DEPT_PLANT);
    if (proxy->save(proxy, moe) == false) abort();

    const struct UserVO *updated = user_vo_new("mstooge", "Moe1", "Stooge1", "moe@stooges.com", "abc123", DEPT_PLANT);
    if (proxy->update(proxy, updated) == false) abort();

    if (strcmp(((struct UserVO *) users->get(users, 2))->first, "Moe1") != 0) abort();
    if (strcmp(((struct UserVO *) users->get(users, 2))->last, "Stooge1") != 0) abort();
}

void test_delete(void) {
    struct IProxy *super = user_proxy_new();
    struct UserProxy *proxy = user_proxy_extend(&(struct UserProxy){}, super);

    struct IArray *users = proxy->find_all(proxy);
    if (users->size(users) != 0) abort();

    const struct UserVO *larry = user_vo_new("lstooge", "Larry", "Stooge", "larry@stooges.com", "ijk456", DEPT_ACCT);
    if (proxy->save(proxy, larry) == false) abort();
    const struct UserVO *curly = user_vo_new("cstooge", "Curly", "Stooge", "curly@stooges.com", "xyz987", DEPT_SALES);
    if (proxy->save(proxy, curly) == false) abort();
    const struct UserVO *moe = user_vo_new("mstooge", "Moe", "Stooge", "moe@stooges.com", "abc123", DEPT_PLANT);
    if (proxy->save(proxy, moe) == false) abort();
    const struct UserVO *shemp = user_vo_new("sstooge", "Shemp", "Stooge", "shemp@stooges.com", "xyz987", DEPT_PLANT);
    if (proxy->save(proxy, shemp) == false) abort();

    if (users->size(users) != 4) abort();

    if (proxy->delete(proxy, curly) == false) abort();
    if (users->size(users) != 3) abort();

    if (strcmp(((struct UserVO *) users->get(users, 0))->username, "lstooge") != 0) abort();
    if (strcmp(((struct UserVO *) users->get(users, 1))->username, "mstooge") != 0) abort();
    if (strcmp(((struct UserVO *) users->get(users, 2))->username, "sstooge") != 0) abort();

    if (proxy->delete(proxy, shemp) == false) abort();
    if (strcmp(((struct UserVO *) users->get(users, 0))->username, "lstooge") != 0) abort();
    if (strcmp(((struct UserVO *) users->get(users, 1))->username, "mstooge") != 0) abort();

    if (proxy->delete(proxy, larry) == false) abort();
    if (strcmp(((struct UserVO *) users->get(users, 0))->username, "mstooge") != 0) abort();

    if (proxy->delete(proxy, moe) == false) abort();
    if (users->size(users) != 0) abort();
}
