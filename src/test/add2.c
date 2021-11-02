#include "driver.h"

#include <stdlib.h>

#include "chattor.h"

void test_1plus2_eq_3(void) {
    int output = add2(1);
    CU_ASSERT_EQUAL(output, 2);
}

void test_pass_but_memleak(void) {
    const char* leaked = malloc(123);
    CU_ASSERT_NOT_EQUAL(leaked, NULL);
}

TESTS {
    SUITE(add2, NULL, NULL);
    TEST(add2, test_1plus2_eq_3);
    TEST(add2, test_pass_but_memleak);
}

