#include <stdbool.h>
#include <string.h>

#include "chattor.h"

#include "add1.c"

bool setup_tests(void) {
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return false;
    }
    CU_pSuite add1_suite = CU_add_suite("add1", NULL, NULL);
    if (add1_suite == NULL) {
        return false;
    }
    if (CU_ADD_TEST(add1_suite, test_1plus1_eq_2) == NULL) { return false; }
    if (CU_ADD_TEST(add1_suite, test_failure) == NULL) { return false; }

    return true;
}

int main(int argc, char** argv) {
    if (!setup_tests()) {
        printf("Failed to build tests: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_run_all_tests();

    CU_pRunSummary summary = CU_get_run_summary();
    printf("Passed %d of %d tests.\n",
            summary->nAsserts - summary->nAssertsFailed,
            summary->nAsserts);

    for (CU_pFailureRecord rec = CU_get_failure_list(); rec != NULL; rec = rec->pNext) {
        const char* filename = rec->strFileName;
        const char* src = strstr(filename, "/src/");
        while (src != NULL) {
            filename = src + 1; // skip the first /
            src = strstr(filename, "/src/");
        }
        printf("%s:%d: %s (%s/%s)\n",
                filename, rec->uiLineNumber,
                rec->strCondition,
                rec->pSuite->pName, rec->pTest->pName);
    }

    CU_cleanup_registry();
}
