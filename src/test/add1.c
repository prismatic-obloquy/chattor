#include <CUnit/TestRun.h>

void test_1plus1_eq_2(void) {
    int output = add1(1);
    CU_ASSERT_EQUAL(output, 2);
}

void test_failure(void) {
    int output = add1(3);
    CU_ASSERT_EQUAL(output, 2);
}
