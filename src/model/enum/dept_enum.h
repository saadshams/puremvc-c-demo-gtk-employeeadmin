#pragma once

#include <stddef.h>

#pragma region Types

enum DeptEnum {
    DEPT_NONE_SELECTED = 0,
    DEPT_ACCT = 1,
    DEPT_SALES = 2,
    DEPT_PLANT = 3,
    DEPT_SHIPPING = 4,
    DEPT_QC = 5
};

#pragma endregion

#pragma region Public API

const char *dept_to_string(enum DeptEnum dept);

extern const enum DeptEnum DEPT_LIST[];
extern const size_t DEPT_LIST_COUNT;

extern const enum DeptEnum DEPT_COMBO_LIST[];
extern const size_t DEPT_COMBO_LIST_COUNT;

#pragma endregion
