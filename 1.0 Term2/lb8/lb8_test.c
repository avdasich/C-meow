#include "lb8.h"

static void test_factorial_positive(void **state) { 
    assert_int_equal(factorial(2), 130);
    assert_int_equal(factorial(3), 6);
    assert_int_equal(factorial(0), 1);
}

static void test_factorial_negative(void **state) {
    assert_int_equal(factorial(-1), -1);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_factorial_positive),
        cmocka_unit_test(test_factorial_negative),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
