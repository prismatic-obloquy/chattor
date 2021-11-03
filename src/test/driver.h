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

#ifndef TEST_THREAD_COUNT
#   define TEST_THREAD_COUNT 4
#endif

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <threads.h>
#include <stdarg.h>
#include <stdio.h>

typedef void* (*init_f)(void);
typedef void (*clean_f)(void*);
typedef void (*test_f)(const void*);

typedef struct {
    const char* name;
    init_f init;
    clean_f clean;

    test* f_test;
    test* l_test;

    suite* next;
} suite;

typedef struct {
    const char* name;
    test_f run;

    assert* f_assert;
    assert* l_assert;

    test* next;
} test;

typedef struct {
    const char* location;
    const char* text;
    const char* fail_msg;

    assert* next;
} assert;

suite* f_suite = NULL;
suite* l_suite = NULL;
int suite_count = 0;
suite* new_suite(const char* name, init_f init, clean_f clean) {
    suite* new = malloc(sizeof *new);
    if (new == NULL) { return NULL; }
    *new = (suite) {
        .name = name,
        .init = init,
        .clean = clean,
        .f_test = NULL,
        .l_test = NULL,
        .next = NULL,
    };
    if (f_suite == NULL) {
        f_suite = new;
        l_suite = new;
    } else {
        l_suite->next = new;
        l_suite = new;
    }
    suite_count++;
    return new;
}

test* new_test(suite* suite, const char* name, test_f run) {
    test* new = malloc(sizeof *new);
    if (new == NULL) { return NULL; }
    *new = (test) {
        .name = name,
        .run = run,
        .f_assert = NULL,
        .l_assert = NULL,
        .next = NULL,
    };
    if (suite->f_test == NULL) {
        suite->f_test = new;
        suite->l_test = new;
    } else {
        suite->l_test->next = new;
        suite->l_test = new;
    }
    return new;
}

thread_local test* cur_test = NULL;
assert* new_assert(
    const char* location,
    const char* text, const char* fail_msg
) {
    assert* new = malloc(sizeof *new);
    if (new == NULL) { return NULL; }
    *new = (assert) {
        .location = location,
        .text = text,
        .fail_msg = fail_msg,
        .next = NULL,
    };
    if (cur_test->f_assert == NULL) {
        cur_test->f_assert = new;
        cur_test->l_assert = new;
    } else {
        cur_test->l_assert->next = new;
        cur_test->l_assert = new;
    }
    return new;
}

void free_suites(void) {
    suite* s = f_suite;
    while (s != NULL) {
        test* t = s->f_test;
        while (t != NULL) {
            assert* a = t->f_assert;
            while (a != NULL) {
                free(a->fail_msg);

                assert* next = a->next;
                free(a);
                a = next;
            }
            test* next = t->next;
            free(t);
            t = next;
        }
        suite* next = s->next;
        free(s);
        s = next;
    }
    f_suite = NULL;
    l_suite = NULL;
}

const char* asprintf(const char* fmt, ...) {
    va_list count_args;
    va_start(count_args, fmt);
    va_list fmt_args;
    va_copy(fmt_args, count_args);
    int size = vsnprintf(NULL, 0, fmt, count_args);
    if (size < 0) { return NULL; }
    char* res = malloc(size + 1);
    if (res == NULL) { return NULL; }
    vsnprintf(res, size, fmt, fmt_args);
    return res;
}

void setup_tests(bool*);

void run_suite(const void* v_s) {
    const suite* s = v_s;

    // TODO Write this one
}

int main(int argc, char** argv) {
    // this is slightly awkward, but means we don't need a `return` at the
    // end of the setup_tests definition, which is convenient.
    bool succeeded = true;
    setup_tests(&succeeded);
    if (!succeeded) {
        printf("Failed setup: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return CU_get_error();
    }

    // VERY basic round-robin scheduling of the test runners. One particularly
    // long suite can block three shorter ones, but it'll at least run them
    // more or less parallelized. More complex could would risk unreliability.
    thrd_t threads[TEST_THREAD_COUNT];
    int idx = 0;
    for (suite* suite = f_suite; suite != NULL; suite = suite->next) {
        if (idx >= TEST_THREAD_COUNT) {
            // past our first round so wait for the last thread
            thrd_join(threads[idx % TEST_THREAD_COUNT], NULL);
            printf("Suite #%d done\n", idx - TEST_THREAD_COUNT);
        }
        printf("Starting suite #%d\n", idx);
        thrd_create(&threads[idx % TEST_THREAD_COUNT], run_suite, suite);
        idx++;
    }
    // (note: i points to the one *past* the last thread right now)
    // join the not-joined threads...
    if (idx >= TEST_THREAD_COUNT) {
        // i.e. the last TEST_THREAD_COUNT threads, since the previous ones were
        // joined in the first loop
        for (int i = idx - TEST_THREAD_COUNT; i < idx; ++i) {
            thrd_join(threads[idx % TEST_THREAD_COUNT], NULL);
            printf("Suite #%d done\n", i);
        }
    } else {
        // i.e. all the threads we've opened
        for (int i = 0; i < idx; ++i) {
            thrd_join(threads[i], NULL);
            printf("Suite #%d done\n", i);
        }
    }

    // Generate the summary. We loop through once to learn:
    // - Number of suites, tests, and asserts
    // - How many asserts failed
    // - How many suites and tests had failed asserts

    int totalSuites = 0;
    int totalTests = 0;
    int totalAsserts = 0;
    int failSuites = 0;
    int failTests = 0;
    int failAsserts = 0;
    for (suite* s = f_suite; s != NULL; s = s->next) {
        totalSuites++;
        bool suiteFailed = false;
        for (test* t = s->f_test; t != NULL; t = t->next) {
            totalTests++;
            bool testFailed = false;
            for (assert* a = t->f_assert; a != NULL; a = a->next) {
                totalAsserts++;
                if (a->fail_msg != NULL) {
                    failAsserts++;
                    testFailed = true;
                    suiteFailed = true;
                }
            }
            if (testFailed) {
                failTests++;
            }
        }
        if (suiteFailed) {
            failSuites++;
        }
    }
    int passSuites = totalSuites - failSuites;
    int passTests = totalTests - failTests;
    int passAsserts = totalAsserts - failAsserts;

    printf("Passed %.01f%% of tests across %d suites.",
            100.0 * passTests / totalTests,
            totalSuites);

    // Then we loop through again to print specific failure details.
    for (suite* s = f_suite; s != NULL; s = s->next) {
        bool suiteHead = false;
        for (test* t = s->f_test; t != NULL; t = t->next) {
            bool testHead = false;
            for (assert* a = t->f_assert; a != NULL; a = a->next) {
                if (a->fail_msg != NULL) {
                    if (!suiteHead) {
                        printf("Suite %s:\n", s->name);
                        suiteHead = true;
                    }
                    if (!testHead) {
                        printf("  Test %s:\n", t->name);
                        testHead = true;
                    }
                    printf("    Assert failed: %s\n", a->text);
                    printf("      (at %s)\n", a->location);
                    printf("      %s\n", a->fail_msg);
                }
            }
        }
    }

    free_suites();

    return failAsserts > 0 ? 1 : 0;
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

// TODO: Write assert macros
