#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "operations.h"
#include "fraction.h"
#include "base_conversion.h"
#include "parser.h"

void test_parse_fraction() {
    printf("Testing fraction parsing...\n");
    
    Fraction *frac = parse_fraction("1/2");
    assert(frac != NULL);
    assert(strcmp(frac->numerator->value, "1") == 0);
    assert(strcmp(frac->denominator->value, "2") == 0);
    free_fraction(frac);
    
    // Test invalid input
    frac = parse_fraction("1");
    assert(frac == NULL);
    
    printf("Fraction parsing tests passed!\n");
}

void test_parse_logarithm() {
    printf("Testing logarithm parsing...\n");
    
    char *base_str, *num_str;
    parse_logarithm("log2(8)", &base_str, &num_str);
    
    assert(strcmp(base_str, "2") == 0);
    assert(strcmp(num_str, "8") == 0);
    
    free(base_str);
    free(num_str);
    
    // Test invalid input
    parse_logarithm("log2", &base_str, &num_str);
    assert(base_str == NULL);
    assert(num_str == NULL);
    
    printf("Logarithm parsing tests passed!\n");
}

int main() {
    printf("Starting main functionality tests...\n\n");
    
    test_parse_fraction();
    test_parse_logarithm();
    
    printf("\nAll main functionality tests passed successfully!\n");
    return 0;
}
