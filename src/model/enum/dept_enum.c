#include "dept_enum.h"

const char *dept_to_string(const enum DeptEnum dept) {
    switch (dept) {
    case NONE_SELECTED: return "--NONE_SELECTED--";
    case ACCT: return "Accounting";
    case SALES: return "Sales";
    case PLANT: return "Plant";
    case SHIPPING: return "Shipping";
    case QC: return "Quality Control";
    default: return "Unknown";
    }
}

const enum DeptEnum DEPT_LIST[] = {
    ACCT,
    SALES,
    PLANT,
    SHIPPING,
    QC
};

const int DEPT_COUNT = sizeof(DEPT_LIST) / sizeof(DEPT_LIST[0]);

const enum DeptEnum DEPT_COMBO_LIST[] = {
    NONE_SELECTED,
    ACCT,
    SALES,
    PLANT,
    SHIPPING,
    QC
};

const int DEPT_COMBO_LIST_COUNT = sizeof(DEPT_COMBO_LIST) / sizeof(DEPT_COMBO_LIST[0]);
