// tests/test_arbitraryint.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/ArbitraryInt.h"

void test_creation() {
    printf("Testing ArbitraryInt creation...\n");
    
    ArbitraryInt *num = create_arbitrary_int("12345");
    assert(num != NULL);
    assert(strcmp(num->value, "12345") == 0);
    assert(num->is_negative == false);
    free_arbitrary_int(num);
    
    // Test negative number
    num = create_arbitrary_int("-54321");
    assert(num != NULL);
    assert(strcmp(num->value, "54321") == 0);
    assert(num->is_negative == true);
    free_arbitrary_int(num);
    
    // Test zero
    num = create_arbitrary_int("0");
    assert(num != NULL);
    assert(strcmp(num->value, "0") == 0);
    assert(num->is_negative == false);
    free_arbitrary_int(num);
    
    // Test leading zeros
    num = create_arbitrary_int("00123");
    assert(num != NULL);
    assert(strcmp(num->value, "123") == 0);
    free_arbitrary_int(num);
    
    printf("Creation tests passed!\n");
}

void test_comparison() {
    printf("Testing ArbitraryInt comparison...\n");
    
    ArbitraryInt *a = create_arbitrary_int("100");
    ArbitraryInt *b = create_arbitrary_int("200");
    assert(compare_arbitrary_ints(a, b) < 0);
    assert(compare_arbitrary_ints(b, a) > 0);
    
    ArbitraryInt *c = create_arbitrary_int("100");
    assert(compare_arbitrary_ints(a, c) == 0);
    
    // Test with negative numbers
    ArbitraryInt *neg = create_arbitrary_int("-100");
    assert(compare_arbitrary_ints(neg, a) < 0);
    
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    free_arbitrary_int(c);
    free_arbitrary_int(neg);
    
    printf("Comparison tests passed!\n");
}

void test_basic_arithmetic() {
    printf("Testing basic arithmetic...\n");
    
    ArbitraryInt *a = create_arbitrary_int("123");
    ArbitraryInt *b = create_arbitrary_int("456");
    
    ArbitraryInt *sum = add_arbitrary_ints(a, b);
    assert(strcmp(sum->value, "579") == 0);
    free_arbitrary_int(sum);
    
    ArbitraryInt *diff = subtract_arbitrary_ints(b, a);
    assert(strcmp(diff->value, "333") == 0);
    free_arbitrary_int(diff);
    
    ArbitraryInt *prod = multiply_arbitrary_ints(a, b);
    assert(strcmp(prod->value, "56088") == 0);
    free_arbitrary_int(prod);
    
    free_arbitrary_int(a);
    free_arbitrary_int(b);
    
    printf("Basic arithmetic tests passed!\n");
}

int main() {
    printf("Starting ArbitraryInt tests...\n\n");
    
    test_creation();
    test_comparison();
    test_basic_arithmetic();
    
    printf("\nAll ArbitraryInt tests passed successfully!\n");
    return 0;
}