#include "unit-driver.h"

#include <stdlib.h>

#include "chattor.h"

void test_1plus2_eq_3(const void* data) {
    (void) data;
    int output = add2(1);
    UDA_EQUAL(output, 2);
}

UD_REGISTER_TESTS {
    UD_SUITE(add2, NULL, NULL);
    UD_TEST(add2, test_1plus2_eq_3);
}

