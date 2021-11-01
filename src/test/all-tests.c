/**********************************************************************\
|                          NOTE TO DEVELOPERS                          |
+----------------------------------------------------------------------+
| Don't write any actual tests in this file. Only add or remove tests  |
| and suites here, in setup_tests. Also don't put any init or cleanup  |
| functions in here, unless they're used in almost all of the tests.   |
|                                                                      |
| There should be roughly one suite per (library) function, where each |
| test will check one facet of the behavior. Each suite gets its own   |
| .c file named after it, which is `#include`d here. Each test should  |
| have 1-3 asserts, though there may need to be more for particularly  |
| complex edge cases, and that's fine. Tests can be tightly bound to   |
| internal behavior as well. For more advice, contact a maintainer.    |
\**********************************************************************/

#include "add1.c"

bool setup_tests(void) {
    SUITE(add1, NULL, NULL);
    TEST(add1, test_1plus1_eq_2);
    TEST(add1, test_failure);
    return true;
}
