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

int main() {
    printf("Starting base conversion tests...\n\n");
    
    test_decimal_to_binary();
    test_decimal_to_hex();
    test_from_binary();
    test_from_hex();
    test_invalid_inputs();
    
    printf("\nAll base conversion tests passed successfully!\n");
    return 0;
}
