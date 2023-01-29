#include "my_module.h"
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_my_module(void) {
    TEST_ASSERT_EQUAL_INT(42, my_module_add(40, 2));
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_my_module);
    return UNITY_END();
}