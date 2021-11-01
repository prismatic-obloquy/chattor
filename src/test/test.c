#include <stdbool.h>
#include <CUnit/Basic.h>

#include "chattor.h"

void test_1plus1_eq_2(void) {
    int output = add1(1);
    CU_ASSERT_EQUAL(output, 2);
}

bool build_tests(void) {
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return false;
    }
    CU_pSuite add1_suite = CU_add_suite("add1", NULL, NULL);
    if (add1_suite == NULL) {
        return false;
    }
    CU_ADD_TEST(add1_suite, test_1plus1_eq_2);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return true;
}

int main(void) {
    if (!build_tests()) {
        printf("Failed to build tests: %s\n", CU_get_error_msg());
    }
}
