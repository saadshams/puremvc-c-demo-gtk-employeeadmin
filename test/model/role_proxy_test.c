#include "role_proxy_test.h"
#include "model/role_proxy.h"
#include "model/value_object/role_vo.h"

#include <stdio.h>
#include <stdlib.h>

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
    printf("\033[1;36m[SUITE] %s\033[0m\n", "RoleProxyTest");
    printf("\033[1;36m================================================\033[0m\n\n");

    beforeAll();
    test("test_add_roles", test_add_roles);
    test("test_remove_roles", test_remove_roles);
    afterAll();

    printf("\n\033[1;32m[DONE] All tests in suite finished.\033[0m\n");
    return 0;
}

void test_add_roles(void) {
    struct IProxy *super = role_proxy_new();
    const struct RoleProxy *proxy = role_proxy_extend(&(struct RoleProxy){}, super);

    proxy->add_item(proxy, role_vo_new("lstooge"));
    proxy->add_role_to_user(proxy, &(struct UserVO) { .username = "lstooge" }, ROLE_ACCT_PAY);

    const struct IArray *role_vos = proxy->find_all(proxy);
    const struct IArray *roles = ((struct RoleVO *) role_vos->get(role_vos, 0))->roles;

    if (*(const enum RoleEnum *) roles->get(roles, 0) != ROLE_ACCT_PAY) abort();
}

void test_remove_roles(void) {
    struct IProxy *super = role_proxy_new();
    const struct RoleProxy *proxy = role_proxy_extend(&(struct RoleProxy){}, super);

    proxy->add_item(proxy, role_vo_new("mstooge"));

    const struct IArray *role_vos = proxy->find_all(proxy);
    const struct IArray *roles = ((struct RoleVO *) role_vos->get(role_vos, 0))->roles;

    proxy->add_role_to_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_PRODUCTION);
    proxy->add_role_to_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_SHIPPING);
    proxy->add_role_to_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_INVENTORY);
    proxy->add_role_to_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_SALES);

    if (*(const enum RoleEnum *) roles->get(roles, 0) != ROLE_PRODUCTION) abort();
    if (*(const enum RoleEnum *) roles->get(roles, 1) != ROLE_SHIPPING) abort();
    if (*(const enum RoleEnum *) roles->get(roles, 2) != ROLE_INVENTORY) abort();
    if (*(const enum RoleEnum *) roles->get(roles, 3) != ROLE_SALES) abort();

    proxy->remove_role_from_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_PRODUCTION);
    if (*(const enum RoleEnum *) roles->get(roles, 0) != ROLE_SHIPPING) abort();
    if (*(const enum RoleEnum *) roles->get(roles, 1) != ROLE_INVENTORY) abort();
    if (*(const enum RoleEnum *) roles->get(roles, 2) != ROLE_SALES) abort();

    proxy->remove_role_from_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_SHIPPING);
    if (*(const enum RoleEnum *) roles->get(roles, 0) != ROLE_INVENTORY) abort();
    if (*(const enum RoleEnum *) roles->get(roles, 1) != ROLE_SALES) abort();

    proxy->remove_role_from_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_INVENTORY);
    if (*(const enum RoleEnum *) roles->get(roles, 0) != ROLE_SALES) abort();

    proxy->remove_role_from_user(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_SALES);
    if (roles->size(roles) != 0) abort();
}
