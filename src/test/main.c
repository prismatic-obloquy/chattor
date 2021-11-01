/**********************************************************************\
|                          NOTE TO DEVELOPERS                          |
+----------------------------------------------------------------------+
| This file orchestrates all the tests. You shouldn't really need to   |
| edit it unless you're changing *how* tests work. If you just want to |
| add or remove tests, see all-tests.c. To change them, edit the test  |
| itself, init, or cleanup functions in the relevant specific .c file. |
\**********************************************************************/

#include <stdbool.h>
#include <string.h>

#include <CUnit/TestRun.h>

#include "chattor.h"

#define SUITE(name, init, cleanup) \
        CU_pSuite name##_suite; \
    do {\
        name##_suite = CU_add_suite(#name, init, cleanup); \
        if (name##_suite == NULL) { return false; } \
    } while(0)
#define TEST(suite, function) \
    do { \
        if (CU_ADD_TEST(suite##_suite, function) == NULL) { \
            return false; \
        } \
    } while (0)

#include "all-tests.c"

int main(int argc, char** argv) {
    if (CUE_SUCCESS != CU_initialize_registry()) {
        printf("Failed to initialize registry: %s\n", CU_get_error_msg());
        return CU_get_error();
    }
    if (!setup_tests()) {
        printf("Failed to build tests: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_run_all_tests();

    puts("");

    CU_pRunSummary summary = CU_get_run_summary();
    printf("Passed %.02f%% of tests (%d/%d)",
            100.0 - (100.0 * summary->nTestsFailed / summary->nTestsRun),
            summary->nTestsRun - summary->nTestsFailed, summary->nTestsRun);

    if (summary->nTestsFailed > 0) {
        puts(". Failed assertions:");
        for (
            CU_pFailureRecord rec = CU_get_failure_list();
            rec != NULL;
            rec = rec->pNext
        ) {
            const char* filename = rec->strFileName;
            const char* src = strstr(filename, "/src/");
            while (src != NULL) {
                filename = src + 1; // skip the first /
                src = strstr(filename, "/src/");
            }
            printf("(%s/%s) %s:%d: %s\n",
                    rec->pSuite->pName, rec->pTest->pName,
                    filename, rec->uiLineNumber,
                    rec->strCondition);
        }

    } else {
        puts("");
    }

    puts("");

    CU_cleanup_registry();
}
