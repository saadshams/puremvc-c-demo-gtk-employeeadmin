#include "role_enum.h"

const char *role_to_string(const enum RoleEnum role) {
    switch (role) {
    case ROLE_NONE_SELECTED: return "--None Selected--";
    case ROLE_ADMIN: return "Administrator";
    case ROLE_ACCT_PAY: return "Accounts Payable";
    case ROLE_ACCT_RCV:      return "Accounts Receivable";
    case ROLE_EMP_BENEFITS:  return "Employee Benefits";
    case ROLE_GEN_LEDGER:    return "General Ledger";
    case ROLE_PAYROLL:       return "Payroll";
    case ROLE_INVENTORY:     return "Inventory";
    case ROLE_PRODUCTION:    return "Production";
    case ROLE_QUALITY_CTL:   return "Quality Control";
    case ROLE_SALES:         return "Sales";
    case ROLE_ORDERS:        return "Orders";
    case ROLE_CUSTOMERS:     return "Customers";
    case ROLE_SHIPPING:      return "Shipping";
    case ROLE_RETURNS:       return "Returns";
    default: return "Unknown";
    }
}

const enum RoleEnum ROLE_LIST[] = {
    ROLE_ADMIN,
    ROLE_ACCT_PAY,
    ROLE_ACCT_RCV,
    ROLE_EMP_BENEFITS,
    ROLE_GEN_LEDGER,
    ROLE_PAYROLL,
    ROLE_INVENTORY,
    ROLE_PRODUCTION,
    ROLE_QUALITY_CTL,
    ROLE_SALES,
    ROLE_ORDERS,
    ROLE_CUSTOMERS,
    ROLE_SHIPPING,
    ROLE_RETURNS
};

const int ROLE_LIST_COUNT = sizeof(ROLE_LIST) / sizeof(ROLE_LIST[0]);

const enum RoleEnum ROLE_COMBO_LIST[] = {
    ROLE_NONE_SELECTED,
    ROLE_ADMIN,
    ROLE_ACCT_PAY,
    ROLE_ACCT_RCV,
    ROLE_EMP_BENEFITS,
    ROLE_GEN_LEDGER,
    ROLE_PAYROLL,
    ROLE_INVENTORY,
    ROLE_PRODUCTION,
    ROLE_QUALITY_CTL,
    ROLE_SALES,
    ROLE_ORDERS,
    ROLE_CUSTOMERS,
    ROLE_SHIPPING,
    ROLE_RETURNS
};

const int ROLE_COMBO_LIST_COUNT = sizeof(ROLE_COMBO_LIST) / sizeof(ROLE_COMBO_LIST[0]);
