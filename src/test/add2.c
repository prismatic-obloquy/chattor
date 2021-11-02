#include "driver.h"

#include "chattor.h"

#include <CUnit/TestRun.h>

void test_1plus2_eq_3(void) {
    int output = add2(1);
    CU_ASSERT_EQUAL(output, 2);
}

void test_1plus2_ne_1(void) {
    int output = add2(1);
    CU_ASSERT_NOT_EQUAL(output, 1);
}

TESTS {
    SUITE(add2, NULL, NULL);
    TEST(add2, test_1plus2_eq_3);
    TEST(add2, test_1plus2_ne_1);
}

