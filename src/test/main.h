#include <stdbool.h>

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

bool setup_tests(void);
