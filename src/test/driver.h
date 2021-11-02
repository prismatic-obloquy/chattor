/**********************************************************************\
|                          NOTE TO DEVELOPERS                          |
+----------------------------------------------------------------------+
| This file orchestrates all the tests. You shouldn't really need to   |
| edit it unless you're changing *how* tests work. If you just want to |
| add or remove tests, see all-tests.c. To change them, edit the test  |
| itself, init, or cleanup functions in the relevant specific .c file. |
|                                                                      |
| The hierarchy of file/suite/test -- because each file is its own     |
| executable and registry -- is a bit complex. In short, there should  |
| be (about) one file per library function, one suite per facet of     |
| that function, and one test per edge case. As a rule of thumb, tests |
| should have 1-3 asserts, but more complex behaviors might need more. |
| Asserts can, and often should, test internal state, to ensure the    |
| function will behave as expected even internally. If you have        |
| questions or want advice, ask a maintainer.                          |
\**********************************************************************/

#include <stdbool.h>
#include <string.h>

#include <CUnit/TestRun.h>

void setup_tests(bool*);

int main(int argc, char** argv) {
    if (CUE_SUCCESS != CU_initialize_registry()) {
        printf("Failed to initialize registry: %s\n", CU_get_error_msg());
        return CU_get_error();
    }
    // this is slightly awkward, but means we don't need a `return` at the
    // end of the setup_tests definition.
    bool succeeded = true;
    setup_tests(&succeeded);
    if (!succeeded) {
        printf("Failed setup: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_run_all_tests();

    CU_pRunSummary summary = CU_get_run_summary();
    printf("Passed %.02f%% of tests (%d/%d)",
            100.0 - (100.0 * summary->nTestsFailed / summary->nTestsRun),
            summary->nTestsRun - summary->nTestsFailed, summary->nTestsRun);

    if (summary->nTestsFailed > 0) {
        puts(". Failed assertions:");
        const char* filename = strrchr(__FILE__, '/') + 1;
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
            printf("- (%s/%s/%s) %s:%d: %s\n",
                    filename, rec->pSuite->pName, rec->pTest->pName,
                    filename, rec->uiLineNumber, rec->strCondition);
        }
    } else {
        puts("");
    }

    bool failed = summary->nTestsFailed > 0;
    CU_cleanup_registry();
    return failed > 0 ? 1 : 0;
}


#define TESTS \
    void setup_tests(bool* succeeded)

#define SUITE(name, init, cleanup) \
        CU_pSuite name##_suite; \
    do {\
        name##_suite = CU_add_suite(#name, init, cleanup); \
        if (name##_suite == NULL) { \
            *succeeded = false; \
            return; \
        } \
    } while(0)

#define TEST(suite, function) \
    do { \
        if (CU_ADD_TEST(suite##_suite, function) == NULL) { \
            *succeeded = false; \
            return; \
        } \
    } while (0)
