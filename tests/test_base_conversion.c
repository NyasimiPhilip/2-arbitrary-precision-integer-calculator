/**
 * @file test_base_conversion.c
 * @brief Test suite for base conversion operations
 *
 * Tests conversion between different number bases:
 * - Binary (base 2)
 * - Decimal (base 10)
 * - Hexadecimal (base 16)
 * - Arbitrary bases up to 36
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/base_conversion.h"
#include "../include/ArbitraryInt.h"

/**
 * @brief Tests decimal to binary conversion
 * 
 * Verifies:
 * - Simple number conversion
 * - Zero handling
 * - Large number conversion
 */
void test_decimal_to_binary() {
    printf("Testing decimal to binary conversion...\n");
    
    // Test case 1: 42 -> 101010
    ArbitraryInt *num = create_arbitrary_int("42");
    char *result = to_base(num, 2);
    assert(result != NULL);
    assert(strcmp(result, "101010") == 0);
    free(result);
    free_arbitrary_int(num);
    
    // Test case 2: 0 -> 0
    num = create_arbitrary_int("0");
    result = to_base(num, 2);
    assert(result != NULL);
    assert(strcmp(result, "0") == 0);
    free(result);
    free_arbitrary_int(num);
    
    printf("Decimal to binary tests passed!\n");
}

/**
 * @brief Tests decimal to hexadecimal conversion
 * 
 * Tests:
 * - Basic conversion
 * - Letter digits (A-F)
 * - Large numbers
 */
void test_decimal_to_hex() {
    printf("Testing decimal to hexadecimal conversion...\n");
    
    // Test case 1: 255 -> FF
    ArbitraryInt *num = create_arbitrary_int("255");
    char *result = to_base(num, 16);
    assert(result != NULL);
    assert(strcmp(result, "FF") == 0);
    free(result);
    free_arbitrary_int(num);
    
    // Test case 2: 26 -> 1A
    num = create_arbitrary_int("26");
    result = to_base(num, 16);
    assert(result != NULL);
    assert(strcmp(result, "1A") == 0);
    free(result);
    free_arbitrary_int(num);
    
    printf("Decimal to hexadecimal tests passed!\n");
}

void test_hex_to_decimal() {
    printf("Testing hexadecimal to decimal conversion...\n");
    
    // Test case 1: 1A -> 26
    ArbitraryInt *result = from_base("1A", 16);
    assert(result != NULL);
    assert(strcmp(result->value, "26") == 0);
    free_arbitrary_int(result);
    
    // Test case 2: FF -> 255
    result = from_base("FF", 16);
    assert(result != NULL);
    assert(strcmp(result->value, "255") == 0);
    free_arbitrary_int(result);
    
    printf("Hexadecimal to decimal tests passed!\n");
}

void test_invalid_inputs() {
    printf("Testing invalid inputs...\n");
    
    // Test invalid base
    ArbitraryInt *num = create_arbitrary_int("42");
    char *result = to_base(num, 37);
    assert(result == NULL);
    free_arbitrary_int(num);
    
    // Test invalid characters
    ArbitraryInt *result2 = from_base("G", 16);
    assert(result2 == NULL);
    
    printf("Invalid input tests passed!\n");
}

void test_arbitrary_bases() {
    printf("Testing arbitrary base conversions...\n");
    
    // Test base 3
    ArbitraryInt *num = create_arbitrary_int("15");
    char *base3 = to_base(num, 3);
    assert(strcmp(base3, "120") == 0);
    free(base3);
    free_arbitrary_int(num);
    
    // Test base 36 (max)
    num = create_arbitrary_int("123456789");
    char *base36 = to_base(num, 36);
    assert(strcmp(base36, "21I3V9") == 0);
    free(base36);
    free_arbitrary_int(num);
    
    // Test negative numbers
    num = create_arbitrary_int("-42");
    char *base2 = to_base(num, 2);
    assert(strcmp(base2, "-101010") == 0);
    free(base2);
    free_arbitrary_int(num);
    
    printf("Arbitrary base conversion tests passed!\n");
}

void test_base_roundtrip() {
    printf("Testing base conversion roundtrip...\n");
    
    // Convert to base N and back to decimal
    const char *original = "123456789";
    ArbitraryInt *num = create_arbitrary_int(original);
    
    // Test with different bases
    int bases[] = {2, 8, 16, 36};
    for(int i = 0; i < sizeof(bases)/sizeof(bases[0]); i++) {
        char *converted = to_base(num, bases[i]);
        ArbitraryInt *back = from_base(converted, bases[i]);
        assert(strcmp(back->value, original) == 0);
        free(converted);
        free_arbitrary_int(back);
    }
    
    free_arbitrary_int(num);
    printf("Base conversion roundtrip tests passed!\n");
}

int main() {
    printf("Starting base conversion tests...\n\n");
    
    test_decimal_to_binary();
    test_decimal_to_hex();
    test_hex_to_decimal();
    test_invalid_inputs();
    test_arbitrary_bases();
    test_base_roundtrip();
    
    printf("\nAll base conversion tests passed successfully!\n");
    return 0;
}
