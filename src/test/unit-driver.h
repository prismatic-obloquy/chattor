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

#ifndef UD_THREAD_COUNT
#   define UD_THREAD_COUNT 0
#endif

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <threads.h>
#include <stdarg.h>
#include <stdio.h>

#define UD_LIST_FIELDS(elem_t, name) \
    elem_t* name##_ary; int name##_cap; int name##_len

#define UD_LIST_INIT(name) \
    .name##_ary = NULL, .name##_cap = 0, .name##_len = 0

#define UD_LIST_ADD(cont, name, elem, success) do { \
    if (cont->name##_cap == cont->name##_len) { \
        int new_cap = cont->name##_cap ? cont->name##_cap * 2 : 4; \
        void* new = realloc(cont->name##_ary, \
                            new_cap * sizeof(cont->name##_ary[0])); \
        if (new == NULL) { \
            success = false; \
        } else { \
            success = true; \
            cont->name##_ary = new; \
            cont->name##_cap = new_cap; \
        } \
    } else { \
        success = true; \
    } \
    if (success) { \
        cont->name##_ary[cont->name##_len++] = elem; \
    } \
} while (0)

#define UD_LIST_FOREACH(cont, name, elem_t, elem) \
    for ( \
        elem_t* elem = cont->name##_ary; \
        elem < cont->name##_ary + cont->name##_len; \
        elem++ \
    )

typedef void* (*UD_init_f)(void);
typedef void (*UD_clean_f)(void*);
typedef void (*UD_test_f)(const void*);

typedef struct {
    // note: not obvious, but fail_msg is the only allocated memory here
    const char* location;
    const char* text;
} UD_assert;

typedef struct {
    const char* name;
    UD_test_f run;

    UD_LIST_FIELDS(UD_assert, asserts);
} UD_test;

typedef struct {
    const char* name;
    UD_init_f init;
    UD_clean_f clean;

    UD_LIST_FIELDS(UD_test, tests);
} UD_suite;

typedef struct {
    UD_LIST_FIELDS(UD_suite, suites);
} UD_registry;

static UD_registry UD_reg = {
    UD_LIST_INIT(suites),
};

UD_suite* UD_add_suite(const char* name, UD_init_f init, UD_clean_f clean) {
    UD_suite new = {
        .name = name,
        .init = init,
        .clean = clean,
        UD_LIST_INIT(tests),
    };
    bool succeeded;
    UD_LIST_ADD((&UD_reg), suites, new, succeeded);
    if (!succeeded) {
        return NULL;
    } else {
        return &UD_reg.suites_ary[UD_reg.suites_len-1];
    }
}

UD_test* UD_add_test(UD_suite* s, const char* name, UD_test_f run) {
    UD_test new = {
        .name = name,
        .run = run,
        UD_LIST_INIT(asserts),
    };
    bool succeeded;
    UD_LIST_ADD(s, tests, new, succeeded);
    if (!succeeded) {
        return NULL;
    } else {
        return &s->tests_ary[s->tests_len-1];
    }
}

UD_assert* UD_add_assert(
    UD_test* t, const char* location,
    const char* text
) {
    UD_assert new = {
        .location = location,
        .text = text,
    };
    bool succeeded;
    UD_LIST_ADD(t, asserts, new, succeeded);
    if (!succeeded) {
        return NULL;
    } else {
        return &t->asserts_ary[t->asserts_len-1];
    }
}

void UD_free_suites(void) {
    UD_LIST_FOREACH((&UD_reg), suites, UD_suite, s) {
        UD_LIST_FOREACH(s, tests, UD_test, t) {
            // nothing to free in each assert, so just free the whole array
            free(t->asserts_ary);
        }
        free(s->tests_ary);
    }
    free(UD_reg.suites_ary);
    // only resetting the outer layer because the rest are inaccessible once
    // it's nulled out
    UD_reg = (UD_registry) {
        UD_LIST_INIT(suites),
    };
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

void UD_setup_tests(bool*);

thread_local UD_test* UD_current_test;
void UD_run_test(UD_test* test, const void* data) {
    UD_current_test = test;
    test->run(data);
}

void UD_pull_tests(void* v_queue) {
    (void) v_queue;
    // TODO: Implement this one
    // - find tasks to pull
    // - run them with UD_run_test
    // - repeat
}

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;
    // this is slightly awkward, but means we don't need a `return` at the
    // end of the UD_setup_tests definition, which is convenient.
    bool succeeded = true;
    UD_setup_tests(&succeeded);
    if (!succeeded) {
        puts("Failed to set up tests");
        UD_free_suites();
        return 1;
    }

#if UD_THREAD_COUNT > 0
    // TODO: parallelize tests better idk
    thrd_t threads[UD_THREAD_COUNT];
    int idx = 0;
    UD_LIST_FOREACH((&UD_reg), suites, UD_suite, s) {
        if (idx >= UD_THREAD_COUNT) {
            // past our first round so wait for the last thread
            thrd_join(threads[idx % UD_THREAD_COUNT], NULL);
            printf("Suite #%d done\n", idx - UD_THREAD_COUNT);
        }
        printf("Starting suite #%d\n", idx);
        thrd_create(&threads[idx % UD_THREAD_COUNT], UD_run_suite, s);
        idx++;
    }
    // (note: i points to the one *past* the last thread right now)
    // join the not-joined threads...
    if (idx >= UD_THREAD_COUNT) {
        // i.e. the last UD_THREAD_COUNT threads, since the previous ones were
        // joined in the first loop
        for (int i = idx - UD_THREAD_COUNT; i < idx; ++i) {
            thrd_join(threads[idx % UD_THREAD_COUNT], NULL);
            printf("Suite #%d done\n", i);
        }
    } else {
        // i.e. all the threads we've opened
        for (int i = 0; i < idx; ++i) {
            thrd_join(threads[i], NULL);
            printf("Suite #%d done\n", i);
        }
    }
#else
    UD_LIST_FOREACH((&UD_reg), suites, UD_suite, s) {
        void* data = s->init ? s->init() : NULL;
        UD_LIST_FOREACH(s, tests, UD_test, t) {
            UD_run_test(t, data);
        }
        if (s->clean) { s->clean(data); };
    }
#endif

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
    UD_LIST_FOREACH((&UD_reg), suites, UD_suite, s) {
        totalSuites++;
        bool suiteFailed = false;
        UD_LIST_FOREACH(s, tests, UD_test, t) {
            totalTests++;
            bool testFailed = false;
            UD_LIST_FOREACH(t, asserts, UD_assert, a) {
                totalAsserts++;
                failAsserts++;
                testFailed = true;
                suiteFailed = true;
            }
            if (testFailed) {
                failTests++;
            }
        }
        if (suiteFailed) {
            failSuites++;
        }
    }
    int passTests = totalTests - failTests;

    printf("Passed %.01f%% of tests across %d suites.",
            100.0 * passTests / totalTests,
            totalSuites);

    // Then we loop through again to print specific failure details.
    UD_LIST_FOREACH((&UD_reg), suites, UD_suite, s) {
        bool suiteHead = false;
        UD_LIST_FOREACH(s, tests, UD_test, t) {
            bool testHead = false;
            UD_LIST_FOREACH(t, asserts, UD_assert, a) {
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
            }
        }
    }

    UD_free_suites();

    return failAsserts > 0 ? 1 : 0;
}


#define UD_REGISTER_TESTS \
    void UD_setup_tests(bool* succeeded)

#define UD_SUITE(name, init, clean) \
    UD_suite* name##_suite; \
    do {\
        name##_suite = UD_add_suite(#name, init, clean); \
        if (name##_suite == NULL) { \
            *succeeded = false; \
            return; \
        } \
    } while(0)

#define UD_TEST(suite, function) \
    do { \
        if (UD_add_test(suite##_suite, #function, function) == NULL) { \
            *succeeded = false; \
            return; \
        } \
    } while (0)

#define UD_STR(x) #x
#define UD_LOCATION __FILE__ ":" UD_STR(__LINE__)

#define UDA_FAIL(message) \
    UD_add_assert(UD_current_test, UD_LOCATION, #message)

#define UDA_TRUE(cond) do { \
    if (!(cond)) { UD_add_assert(UD_current_test, UD_LOCATION, #cond); } \
} while(0)

#define UDA_EQUAL(lhs, rhs) UDA_TRUE(lhs == rhs)
#define UDA_NOT_EQUAL(lhs, rhs) UDA_TRUE(lhs != rhs)
