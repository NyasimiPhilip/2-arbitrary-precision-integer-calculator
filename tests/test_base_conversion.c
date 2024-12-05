#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/base_conversion.h"
#include "../src/ArbitraryInt.h"

void test_decimal_to_binary() {
    printf("Testing decimal to binary conversion...\n");
    
    ArbitraryInt *num = create_arbitrary_int("42");
    char *binary = to_base(num, 2);
    assert(strcmp(binary, "101010") == 0);
    free(binary);
    free_arbitrary_int(num);
    
    num = create_arbitrary_int("0");
    binary = to_base(num, 2);
    assert(strcmp(binary, "0") == 0);
    free(binary);
    free_arbitrary_int(num);
    
    printf("Decimal to binary tests passed!\n");
}

void test_decimal_to_hex() {
    printf("Testing decimal to hexadecimal conversion...\n");
    
    ArbitraryInt *num = create_arbitrary_int("255");
    char *hex = to_base(num, 16);
    assert(strcmp(hex, "FF") == 0);
    free(hex);
    free_arbitrary_int(num);
    
    num = create_arbitrary_int("4096");
    hex = to_base(num, 16);
    assert(strcmp(hex, "1000") == 0);
    free(hex);
    free_arbitrary_int(num);
    
    printf("Decimal to hexadecimal tests passed!\n");
}

void test_from_binary() {
    printf("Testing binary to decimal conversion...\n");
    
    ArbitraryInt *num = from_base("101010", 2);
    assert(strcmp(num->value, "42") == 0);
    free_arbitrary_int(num);
    
    num = from_base("0", 2);
    assert(strcmp(num->value, "0") == 0);
    free_arbitrary_int(num);
    
    printf("Binary to decimal tests passed!\n");
}

void test_from_hex() {
    printf("Testing hexadecimal to decimal conversion...\n");
    
    ArbitraryInt *num = from_base("FF", 16);
    assert(strcmp(num->value, "255") == 0);
    free_arbitrary_int(num);
    
    num = from_base("1000", 16);
    assert(strcmp(num->value, "4096") == 0);
    free_arbitrary_int(num);
    
    printf("Hexadecimal to decimal tests passed!\n");
}

void test_invalid_inputs() {
    printf("Testing invalid inputs...\n");
    
    // Invalid base
    ArbitraryInt *num = create_arbitrary_int("42");
    char *result = to_base(num, 37);
    assert(result == NULL);
    free_arbitrary_int(num);
    
    // Invalid characters
    ArbitraryInt *invalid = from_base("G", 16);
    assert(invalid == NULL);
    
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
    test_from_binary();
    test_from_hex();
    test_invalid_inputs();
    test_arbitrary_bases();
    test_base_roundtrip();
    
    printf("\nAll base conversion tests passed successfully!\n");
    return 0;
}
