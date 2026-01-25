#pragma once

enum DeptEnum {
    NONE_SELECTED = -1,
    ACCT = 0,
    SALES = 1,
    PLANT = 2,
    SHIPPING = 3,
    QC = 4
};

const char *dept_to_string(enum DeptEnum dept);

extern const enum DeptEnum DEPT_LIST[];
extern const int DEPT_LIST_COUNT;

extern const enum DeptEnum DEPT_COMBO_LIST[];
extern const int DEPT_COMBO_LIST_COUNT;
