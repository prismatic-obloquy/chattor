#include "driver.h"

#include "chattor.h"

void test_1plus1_eq_2(void) {
    int output = add1(1);
    CU_ASSERT_EQUAL(output, 2);
}

TESTS {
    SUITE(add1, NULL, NULL);
    TEST(add1, test_1plus1_eq_2);
}
