#include "unit-driver.h"

#include "chattor.h"

#include <CUnit/TestRun.h>

void test_1plus1_eq_2(const void* data) {
    (void) data;
    int output = add1(1);
    UDA_EQUAL(output, 2);
}

UD_REGISTER_TESTS {
    UD_SUITE(add1, NULL, NULL);
    UD_TEST(add1, test_1plus1_eq_2);
}
