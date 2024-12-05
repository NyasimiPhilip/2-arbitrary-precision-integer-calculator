#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/operations.h"

void test_basic_arithmetic() {
    ArbitraryInt *a, *b, *result;
    
    // Addition tests
    printf("Testing addition...\n");
    a = create_arbitrary_int("123456789");
    b = create_arbitrary_int("987654321");
    result = add(a, b);
    assert(strcmp(result->value, "1111111110") == 0);
    free_arbitrary_int(result);
    
    // Test negative numbers
    a->is_negative = true;
    result = add(a, b);
    assert(strcmp(result->value, "864197532") == 0);
    assert(result->is_negative == false);
    free_arbitrary_int(result);
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    
    // Subtraction tests
    printf("Testing subtraction...\n");
    a = create_arbitrary_int("1000000000");
    b = create_arbitrary_int("1");
    result = subtract(a, b);
    assert(strcmp(result->value, "999999999") == 0);
    free_arbitrary_int(result);
    
    // Test negative result
    result = subtract(b, a);
    assert(strcmp(result->value, "999999999") == 0);
    assert(result->is_negative == true);
    free_arbitrary_int(result);
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    
    // Multiplication tests
    printf("Testing multiplication...\n");
    a = create_arbitrary_int("12345");
    b = create_arbitrary_int("98765");
    result = multiply(a, b);
    assert(strcmp(result->value, "1219253925") == 0);
    free_arbitrary_int(result);
    
    // Test multiplication by zero
    b = create_arbitrary_int("0");
    result = multiply(a, b);
    assert(strcmp(result->value, "0") == 0);
    free_arbitrary_int(result);
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    
    printf("Basic arithmetic tests passed!\n");
}

void test_division_and_modulo() {
    printf("Testing division and modulo...\n");
    
    // Basic division
    ArbitraryInt *a = create_arbitrary_int("1000");
    ArbitraryInt *b = create_arbitrary_int("3");
    ArbitraryInt *remainder = NULL;
    ArbitraryInt *quotient = divide(a, b, &remainder);
    assert(strcmp(quotient->value, "333") == 0);
    assert(strcmp(remainder->value, "1") == 0);
    free_arbitrary_int(quotient);
    free_arbitrary_int(remainder);
    
    // Test division by zero cases
    printf("Testing division by zero cases...\n");
    
    // Case 1: 1/0 (Positive Infinity)
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    a = create_arbitrary_int("1");
    b = create_arbitrary_int("0");
    quotient = divide(a, b, &remainder);
    assert(quotient == NULL); // Should return NULL for infinity
    
    // Case 2: -1/0 (Negative Infinity)
    free_arbitrary_int(a);
    a = create_arbitrary_int("-1");
    quotient = divide(a, b, &remainder);
    assert(quotient == NULL); // Should return NULL for -infinity
    
    // Case 3: 0/0 (NaN)
    free_arbitrary_int(a);
    a = create_arbitrary_int("0");
    quotient = divide(a, b, &remainder);
    assert(quotient == NULL); // Should return NULL for NaN
    
    // Test modulo operations
    printf("Testing modulo operations...\n");
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    
    a = create_arbitrary_int("7");
    b = create_arbitrary_int("3");
    ArbitraryInt *mod_result = modulo(a, b);
    assert(strcmp(mod_result->value, "1") == 0);
    free_arbitrary_int(mod_result);
    
    // Test large number modulo
    free_arbitrary_int(a);
    a = create_arbitrary_int("1000000");
    mod_result = modulo(a, b);
    assert(strcmp(mod_result->value, "1") == 0);
    free_arbitrary_int(mod_result);
    
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    
    printf("Division and modulo tests passed!\n");
}

void test_power() {
    ArbitraryInt *base, *exp, *result;
    
    printf("Testing power function...\n");
    
    // Test 2^10
    base = create_arbitrary_int("2");
    exp = create_arbitrary_int("10");
    result = power(base, exp);
    assert(strcmp(result->value, "1024") == 0);
    free_arbitrary_int(result);
    
    // Test negative exponent (should return NULL)
    exp->is_negative = true;
    result = power(base, exp);
    assert(result == NULL);
    
    // Test 0^0 (defined as 1 in this implementation)
    free_arbitrary_int(base);
    free_arbitrary_int(exp);
    base = create_arbitrary_int("0");
    exp = create_arbitrary_int("0");
    result = power(base, exp);
    assert(strcmp(result->value, "1") == 0);
    free_arbitrary_int(result);
    free_arbitrary_int(base);
    free_arbitrary_int(exp);
    
    printf("Power function tests passed!\n");
}

void test_factorial() {
    ArbitraryInt *n, *result;
    
    printf("Testing factorial...\n");
    
    // Test 5!
    n = create_arbitrary_int("5");
    result = factorial(n);
    assert(strcmp(result->value, "120") == 0);
    free_arbitrary_int(result);
    
    // Test 0!
    free_arbitrary_int(n);
    n = create_arbitrary_int("0");
    result = factorial(n);
    assert(strcmp(result->value, "1") == 0);
    free_arbitrary_int(result);
    
    // Test negative number (should return NULL)
    n->is_negative = true;
    result = factorial(n);
    assert(result == NULL);
    free_arbitrary_int(n);
    
    printf("Factorial tests passed!\n");
}

void test_logarithm() {
    ArbitraryInt *num, *base, *result;
    
    printf("Testing logarithm...\n");
    
    // Test log2(8) = 3
    num = create_arbitrary_int("8");
    base = create_arbitrary_int("2");
    result = logarithm(num, base);
    assert(strcmp(result->value, "3") == 0);
    free_arbitrary_int(result);
    
    // Test log10(1000) = 3
    free_arbitrary_int(num);
    free_arbitrary_int(base);
    num = create_arbitrary_int("1000");
    base = create_arbitrary_int("10");
    result = logarithm(num, base);
    assert(strcmp(result->value, "3") == 0);
    free_arbitrary_int(result);
    
    // Test error cases
    // Test log(0)
    free_arbitrary_int(num);
    free_arbitrary_int(base);
    num = create_arbitrary_int("0");
    base = create_arbitrary_int("2");
    result = logarithm(num, base);
    assert(result == NULL);
    
    // Test negative number
    num->is_negative = true;
    result = logarithm(num, base);
    assert(result == NULL);
    
    // Test invalid base
    free_arbitrary_int(base);
    base = create_arbitrary_int("1");
    result = logarithm(num, base);
    assert(result == NULL);
    
    free_arbitrary_int(num);
    free_arbitrary_int(base);
    
    printf("Logarithm tests passed!\n");
}

void test_edge_cases() {
    ArbitraryInt *a, *b, *result;
    
    printf("Testing edge cases...\n");
    
    // Test very large numbers
    a = create_arbitrary_int("999999999999999999999999999999");
    b = create_arbitrary_int("1");
    result = add(a, b);
    assert(strcmp(result->value, "1000000000000000000000000000000") == 0);
    free_arbitrary_int(result);
    
    // Test operations with zero
    result = multiply(a, b);
    assert(strcmp(result->value, "999999999999999999999999999999") == 0);
    free_arbitrary_int(result);
    
    free_arbitrary_int(b);
    b = create_arbitrary_int("0");
    result = add(a, b);
    assert(strcmp(result->value, "999999999999999999999999999999") == 0);
    free_arbitrary_int(result);
    
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    
    printf("Edge case tests passed!\n");
}

void test_logarithm_comprehensive() {
    printf("Testing comprehensive logarithm cases...\n");
    
    // Test powers of 2
    ArbitraryInt *base = create_arbitrary_int("2");
    ArbitraryInt *nums[] = {
        create_arbitrary_int("2"),
        create_arbitrary_int("4"),
        create_arbitrary_int("8"),
        create_arbitrary_int("16"),
        create_arbitrary_int("32")
    };
    
    for(int i = 0; i < 5; i++) {
        ArbitraryInt *result = logarithm(nums[i], base);
        char expected[2];
        sprintf(expected, "%d", i + 1);
        assert(strcmp(result->value, expected) == 0);
        free_arbitrary_int(result);
    }
    
    free_arbitrary_int(base);
    for(int i = 0; i < 5; i++) {
        free_arbitrary_int(nums[i]);
    }
    
    // Test powers of 10
    base = create_arbitrary_int("10");
    ArbitraryInt *num = create_arbitrary_int("1000000");
    ArbitraryInt *result = logarithm(num, base);
    assert(strcmp(result->value, "6") == 0);
    
    free_arbitrary_int(base);
    free_arbitrary_int(num);
    free_arbitrary_int(result);
    
    printf("Comprehensive logarithm tests passed!\n");
}

void test_logarithm_errors() {
    printf("Testing logarithm error cases...\n");
    
    // Test negative number
    ArbitraryInt *base = create_arbitrary_int("2");
    ArbitraryInt *num = create_arbitrary_int("-8");
    ArbitraryInt *result = logarithm(num, base);
    assert(result == NULL);
    
    // Test zero
    free_arbitrary_int(num);
    num = create_arbitrary_int("0");
    result = logarithm(num, base);
    assert(result == NULL);
    
    // Test base 1
    free_arbitrary_int(base);
    base = create_arbitrary_int("1");
    num = create_arbitrary_int("10");
    result = logarithm(num, base);
    assert(result == NULL);
    
    free_arbitrary_int(base);
    free_arbitrary_int(num);
    
    printf("Logarithm error case tests passed!\n");
}

int main() {
    printf("Starting tests...\n\n");
    
    test_basic_arithmetic();
    test_division_and_modulo();
    test_power();
    test_factorial();
    test_logarithm();
    test_edge_cases();
    test_logarithm_comprehensive();
    test_logarithm_errors();
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}
