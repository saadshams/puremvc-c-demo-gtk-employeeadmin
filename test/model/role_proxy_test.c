#include "role_proxy_test.h"
#include "model/role_proxy.h"

#import "model/valueObject/role_vo.h"

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
    test("testAddRoles", testAddRoles);
    test("testAddLimit", testAddLimit);
    test("testRemoveRoles", testRemoveRoles);
    afterAll();

    printf("\n\033[1;32m[DONE] All tests in suite finished.\033[0m\n");
    return 0;
}

void testAddRoles(void) {
    struct RoleVO **roles = (struct RoleVO *[]) {
        &(struct RoleVO) { .username = "lstooge", .roles ={ ROLE_PAYROLL, ROLE_EMP_BENEFITS } },
        &(struct RoleVO) { .username = "cstooge", .roles = { ROLE_ACCT_PAY, ROLE_ACCT_RCV, ROLE_GEN_LEDGER } },
        &(struct RoleVO) { .username = "mstooge", .roles = { ROLE_INVENTORY, ROLE_PRODUCTION, ROLE_SALES, ROLE_SHIPPING } },
        NULL
    };

    struct IProxy *super = role_proxy_init(alloca(puremvc_proxy_size()), "RoleProxyTest", roles);
    const struct RoleProxy *proxy = role_proxy_bind(&(struct RoleProxy){}, super);

    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "lstooge" }, ROLE_ACCT_PAY);
    if (roles[0]->roles[0] != ROLE_PAYROLL) abort();
    if (roles[0]->roles[1] != ROLE_EMP_BENEFITS) abort();
    if (roles[0]->roles[2] != ROLE_ACCT_PAY) abort();
    if (roles[0]->roles[3] != ROLE_NONE_SELECTED) abort();
}

void testAddLimit(void) {
    struct RoleVO **roles = (struct RoleVO *[]) {
        &(struct RoleVO) { .username = "lstooge", .roles ={ ROLE_PAYROLL, ROLE_EMP_BENEFITS } },
        &(struct RoleVO) { .username = "cstooge", .roles = { ROLE_ACCT_PAY, ROLE_ACCT_RCV, ROLE_GEN_LEDGER } },
        &(struct RoleVO) { .username = "mstooge", .roles = { ROLE_INVENTORY, ROLE_PRODUCTION, ROLE_SALES, ROLE_SHIPPING } },
        &(struct RoleVO) { .username = "sshemp", .roles = {ROLE_ADMIN, ROLE_ACCT_PAY, ROLE_ACCT_RCV, ROLE_EMP_BENEFITS, ROLE_GEN_LEDGER, ROLE_PAYROLL, ROLE_INVENTORY} },
        NULL
    };

    struct IProxy *super = role_proxy_init(alloca(puremvc_proxy_size()), "RoleProxyTest", roles);
    const struct RoleProxy *proxy = role_proxy_bind(&(struct RoleProxy){}, super);

    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "sshemp" }, ROLE_PRODUCTION);
    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "sshemp" }, ROLE_QUALITY_CTL);
    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "sshemp" }, ROLE_SALES);
    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "sshemp" }, ROLE_ORDERS);
    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "sshemp" }, ROLE_CUSTOMERS);
    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "sshemp" }, ROLE_SHIPPING);
    proxy->addRoleToUser(proxy, &(struct UserVO) { .username = "sshemp" }, ROLE_RETURNS);

    if (roles[3]->roles[0] != ROLE_ADMIN) abort();
    if (roles[3]->roles[1] != ROLE_ACCT_PAY) abort();
    if (roles[3]->roles[2] != ROLE_ACCT_RCV) abort();
    if (roles[3]->roles[3] != ROLE_EMP_BENEFITS) abort();
    if (roles[3]->roles[4] != ROLE_GEN_LEDGER) abort();
    if (roles[3]->roles[5] != ROLE_PAYROLL) abort();
    if (roles[3]->roles[6] != ROLE_INVENTORY) abort();

    if (roles[3]->roles[7] != ROLE_PRODUCTION) abort();
    if (roles[3]->roles[8] != ROLE_QUALITY_CTL) abort();
    if (roles[3]->roles[9] != ROLE_SALES) abort();
    if (roles[3]->roles[10] != ROLE_ORDERS) abort();
    if (roles[3]->roles[11] != ROLE_CUSTOMERS) abort();
    if (roles[3]->roles[12] != ROLE_SHIPPING) abort();
    if (roles[3]->roles[13] != ROLE_RETURNS) abort();
    if (roles[3]->roles[14] != ROLE_NONE_SELECTED) abort();
}

void testRemoveRoles(void) {
    struct RoleVO **roles = (struct RoleVO *[]) {
        &(struct RoleVO) { .username = "lstooge", .roles ={ ROLE_PAYROLL, ROLE_EMP_BENEFITS } },
        &(struct RoleVO) { .username = "cstooge", .roles = { ROLE_ACCT_PAY, ROLE_ACCT_RCV, ROLE_GEN_LEDGER } },
        &(struct RoleVO) { .username = "mstooge", .roles = { ROLE_INVENTORY, ROLE_PRODUCTION, ROLE_SALES, ROLE_SHIPPING } },
        NULL
    };

    struct IProxy *super = role_proxy_init(alloca(puremvc_proxy_size()), "RoleProxyTest", roles);
    const struct RoleProxy *proxy = role_proxy_bind(&(struct RoleProxy){}, super);

    proxy->removeRoleFromUser(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_PRODUCTION);
    if (roles[2]->roles[0] != ROLE_INVENTORY) abort();
    if (roles[2]->roles[1] != ROLE_SALES) abort();
    if (roles[2]->roles[2] != ROLE_SHIPPING) abort();
    if (roles[2]->roles[3] != ROLE_NONE_SELECTED) abort();

    proxy->removeRoleFromUser(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_SHIPPING);
    if (roles[2]->roles[0] != ROLE_INVENTORY) abort();
    if (roles[2]->roles[1] != ROLE_SALES) abort();
    if (roles[2]->roles[2] != ROLE_NONE_SELECTED) abort();
    if (roles[2]->roles[3] != ROLE_NONE_SELECTED) abort();

    proxy->removeRoleFromUser(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_INVENTORY);
    if (roles[2]->roles[0] != ROLE_SALES) abort();
    if (roles[2]->roles[1] != ROLE_NONE_SELECTED) abort();
    if (roles[2]->roles[2] != ROLE_NONE_SELECTED) abort();
    if (roles[2]->roles[3] != ROLE_NONE_SELECTED) abort();

    proxy->removeRoleFromUser(proxy, &(struct UserVO) { .username = "mstooge" }, ROLE_SALES);
    if (roles[2]->roles[0] != ROLE_NONE_SELECTED) abort();
    if (roles[2]->roles[1] != ROLE_NONE_SELECTED) abort();
    if (roles[2]->roles[2] != ROLE_NONE_SELECTED) abort();
    if (roles[2]->roles[3] != ROLE_NONE_SELECTED) abort();
}
