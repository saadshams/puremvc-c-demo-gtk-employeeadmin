#pragma once

enum RoleEnum {
    NONE_SELECTED = -1,
    ADMIN = 0,
    ACCT_PAY = 1,
    ACCT_RCV = 2,
    EMP_BENEFITS = 3,
    GEN_LEDGER = 4,
    PAYROLL = 5,
    INVENTORY = 6,
    PRODUCTION = 7,
    QUALITY_CTL = 8,
    SALES = 9,
    ORDERS = 10,
    CUSTOMERS = 11,
    SHIPPING = 12,
    RETURNS = 13
};

const char *role_to_string(enum RoleEnum role);

extern const enum RoleEnum ROLE_LIST[];
extern const int ROLE_LIST_COUNT;

extern const enum RoleEnum ROLE_COMBO_LIST[];
extern const int ROLE_COMBO_LIST_COUNT;
