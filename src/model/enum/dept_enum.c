#include "dept_enum.h"

#pragma region Constants

const enum DeptEnum DEPT_LIST[] = {
    DEPT_ACCT,
    DEPT_SALES,
    DEPT_PLANT,
    DEPT_SHIPPING,
    DEPT_QC
};

const size_t DEPT_COUNT = sizeof(DEPT_LIST) / sizeof(DEPT_LIST[0]);

const enum DeptEnum DEPT_COMBO_LIST[] = {
    DEPT_NONE_SELECTED,
    DEPT_ACCT,
    DEPT_SALES,
    DEPT_PLANT,
    DEPT_SHIPPING,
    DEPT_QC
};

const size_t DEPT_COMBO_LIST_COUNT = sizeof(DEPT_COMBO_LIST) / sizeof(DEPT_COMBO_LIST[0]);

#pragma endregion

#pragma region Accessors

const char *dept_to_string(const enum DeptEnum dept) {
    switch (dept) {
        case DEPT_NONE_SELECTED: return "--NONE_SELECTED--";
        case DEPT_ACCT: return "Accounting";
        case DEPT_SALES: return "Sales";
        case DEPT_PLANT: return "Plant";
        case DEPT_SHIPPING: return "Shipping";
        case DEPT_QC: return "Quality Control";
        default: return "Unknown";
    }
}

#pragma endregion
