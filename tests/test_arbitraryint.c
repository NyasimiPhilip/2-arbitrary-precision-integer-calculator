// tests/test_arbitraryint.c
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "ArbitraryInt.h"

void test_create_arbitrary_int(void) {
    ArbitraryInt *num = create_arbitrary_int("-12345");
    CU_ASSERT_TRUE(num->is_negative);
    CU_ASSERT_STRING_EQUAL(num->value, "12345");
    free_arbitrary_int(num);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("ArbitraryInt_Test_Suite", 0, 0);
    CU_add_test(suite, "test_create_arbitrary_int", test_create_arbitrary_int);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}