#pragma once

enum RoleEnum {
    ROLE_NONE_SELECTED = 0,
    ROLE_ADMIN = 1,
    ROLE_ACCT_PAY = 2,
    ROLE_ACCT_RCV = 3,
    ROLE_EMP_BENEFITS = 4,
    ROLE_GEN_LEDGER = 5,
    ROLE_PAYROLL = 6,
    ROLE_INVENTORY = 7,
    ROLE_PRODUCTION = 8,
    ROLE_QUALITY_CTL = 9,
    ROLE_SALES = 10,
    ROLE_ORDERS = 11,
    ROLE_CUSTOMERS = 12,
    ROLE_SHIPPING = 13,
    ROLE_RETURNS = 14
};

const char *role_to_string(enum RoleEnum role);

extern const enum RoleEnum ROLE_LIST[];
extern const int ROLE_LIST_COUNT;

extern const enum RoleEnum ROLE_COMBO_LIST[];
extern const int ROLE_COMBO_LIST_COUNT;
