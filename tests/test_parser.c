#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/parser.h"

void test_fraction_parser() {
    printf("Testing fraction parser...\n");
    
    // Test basic fraction
    Fraction* f = parse_fraction("1/2");
    assert(f != NULL);
    assert(strcmp(f->numerator->value, "1") == 0);
    assert(strcmp(f->denominator->value, "2") == 0);
    free_fraction(f);
    
    // Test with whitespace
    f = parse_fraction(" 123 / 456 ");
    assert(f != NULL);
    assert(strcmp(f->numerator->value, "123") == 0);
    assert(strcmp(f->denominator->value, "456") == 0);
    free_fraction(f);
    
    // Test negative numbers
    f = parse_fraction("-1/2");
    assert(f != NULL);
    assert(f->numerator->is_negative);
    free_fraction(f);
    
    // Test invalid inputs
    assert(parse_fraction(NULL) == NULL);
    assert(parse_fraction("") == NULL);
    assert(parse_fraction("1") == NULL);
    assert(parse_fraction("1/") == NULL);
    assert(parse_fraction("/2") == NULL);
    assert(parse_fraction("a/b") == NULL);
    
    printf("Fraction parser tests passed!\n");
}

void test_logarithm_parser() {
    printf("Testing logarithm parser...\n");
    
    char *base_str, *num_str;
    
    // Test basic logarithm
    parse_logarithm("log2(8)", &base_str, &num_str);
    assert(strcmp(base_str, "2") == 0);
    assert(strcmp(num_str, "8") == 0);
    free(base_str);
    free(num_str);
    
    // Test with whitespace
    parse_logarithm(" log10 ( 1000 ) ", &base_str, &num_str);
    assert(strcmp(base_str, "10") == 0);
    assert(strcmp(num_str, "1000") == 0);
    free(base_str);
    free(num_str);
    
    // Test default base 10
    parse_logarithm("log(100)", &base_str, &num_str);
    assert(strcmp(base_str, "10") == 0);
    assert(strcmp(num_str, "100") == 0);
    free(base_str);
    free(num_str);
    
    // Test invalid inputs
    parse_logarithm(NULL, &base_str, &num_str);
    assert(base_str == NULL && num_str == NULL);
    
    parse_logarithm("log", &base_str, &num_str);
    assert(base_str == NULL && num_str == NULL);
    
    parse_logarithm("log2", &base_str, &num_str);
    assert(base_str == NULL && num_str == NULL);
    
    parse_logarithm("log2()", &base_str, &num_str);
    assert(base_str == NULL && num_str == NULL);
    
    printf("Logarithm parser tests passed!\n");
}

int main() {
    printf("Starting parser tests...\n\n");
    
    test_fraction_parser();
    test_logarithm_parser();
    
    printf("\nAll parser tests passed successfully!\n");
    return 0;
}
