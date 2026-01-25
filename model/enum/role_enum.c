#include "role_enum.h"

const char *role_to_string(const enum RoleEnum role) {
    switch (role) {
    case NONE_SELECTED: return "--None Selected--";
    case ADMIN: return "Administrator";
    case ACCT_PAY: return "Accounts Payable";
    case ACCT_RCV:      return "Accounts Receivable";
    case EMP_BENEFITS:  return "Employee Benefits";
    case GEN_LEDGER:    return "General Ledger";
    case PAYROLL:       return "Payroll";
    case INVENTORY:     return "Inventory";
    case PRODUCTION:    return "Production";
    case QUALITY_CTL:   return "Quality Control";
    case SALES:         return "Sales";
    case ORDERS:        return "Orders";
    case CUSTOMERS:     return "Customers";
    case SHIPPING:      return "Shipping";
    case RETURNS:       return "Returns";
    default: return "Unknown";
    }
}

const enum RoleEnum ROLE_LIST[] = {
    ADMIN,
    ACCT_PAY,
    ACCT_RCV,
    EMP_BENEFITS,
    GEN_LEDGER,
    PAYROLL,
    INVENTORY,
    PRODUCTION,
    QUALITY_CTL,
    SALES,
    ORDERS,
    CUSTOMERS,
    SHIPPING,
    RETURNS
};

const int ROLE_LIST_COUNT = sizeof(ROLE_LIST) / sizeof(ROLE_LIST[0]);

const enum RoleEnum ROLE_COMBO_LIST[] = {
    NONE_SELECTED,
    ADMIN,
    ACCT_PAY,
    ACCT_RCV,
    EMP_BENEFITS,
    GEN_LEDGER,
    PAYROLL,
    INVENTORY,
    PRODUCTION,
    QUALITY_CTL,
    SALES,
    ORDERS,
    CUSTOMERS,
    SHIPPING,
    RETURNS
};

const int ROLE_COMBO_LIST_COUNT = sizeof(ROLE_COMBO_LIST) / sizeof(ROLE_COMBO_LIST[0]);
