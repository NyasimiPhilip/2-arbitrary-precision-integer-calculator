#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/fraction.h"
#include "../include/parser.h"

void test_fraction_creation() {
    printf("Testing fraction creation...\n");
    
    ArbitraryInt *num = create_arbitrary_int("1");
    ArbitraryInt *den = create_arbitrary_int("2");
    Fraction *frac = create_fraction(num, den);
    
    assert(strcmp(frac->numerator->value, "1") == 0);
    assert(strcmp(frac->denominator->value, "2") == 0);
    
    free_fraction(frac);
    free_arbitrary_int(num);
    free_arbitrary_int(den);
    
    printf("Fraction creation tests passed!\n");
}

void test_fraction_simplification() {
    printf("Testing fraction simplification...\n");
    
    // Test 2/4 = 1/2
    ArbitraryInt *num = create_arbitrary_int("2");
    ArbitraryInt *den = create_arbitrary_int("4");
    Fraction *frac = create_fraction(num, den);
    
    assert(strcmp(frac->numerator->value, "1") == 0);
    assert(strcmp(frac->denominator->value, "2") == 0);
    
    free_fraction(frac);
    free_arbitrary_int(num);
    free_arbitrary_int(den);
    
    printf("Fraction simplification tests passed!\n");
}

void test_fraction_addition() {
    printf("Testing fraction addition...\n");
    
    // Test 1/2 + 1/12 = 7/12
    Fraction *f1 = parse_fraction("1/2");
    Fraction *f2 = parse_fraction("1/12");
    
    Fraction *sum = add_fractions(f1, f2);
    assert(strcmp(sum->numerator->value, "7") == 0);
    assert(strcmp(sum->denominator->value, "12") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(sum);
    
    // Test 3/4 + 1/2 = 5/4
    f1 = parse_fraction("3/4");
    f2 = parse_fraction("1/2");
    
    sum = add_fractions(f1, f2);
    assert(strcmp(sum->numerator->value, "5") == 0);
    assert(strcmp(sum->denominator->value, "4") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(sum);
    
    printf("Fraction addition tests passed!\n");
}

void test_fraction_multiplication() {
    printf("Testing fraction multiplication...\n");
    
    // Test 2/3 * 3/4 = 1/2
    Fraction *f1 = parse_fraction("2/3");
    Fraction *f2 = parse_fraction("3/4");
    
    Fraction *prod = multiply_fractions(f1, f2);
    assert(strcmp(prod->numerator->value, "1") == 0);
    assert(strcmp(prod->denominator->value, "2") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(prod);
    
    printf("Fraction multiplication tests passed!\n");
}

void test_fraction_division() {
    printf("Testing fraction division...\n");
    
    // Test 3/4 / 1/2 = 3/2
    Fraction *f1 = parse_fraction("3/4");
    Fraction *f2 = parse_fraction("1/2");
    
    Fraction *quot = divide_fractions(f1, f2);
    assert(strcmp(quot->numerator->value, "3") == 0);
    assert(strcmp(quot->denominator->value, "2") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(quot);
    
    printf("Fraction division tests passed!\n");
}

void test_fraction_subtraction() {
    printf("Testing fraction subtraction...\n");
    
    // Test 1/2 - 1/3 = 1/6
    Fraction *f1 = parse_fraction("1/2");
    Fraction *f2 = parse_fraction("1/3");
    
    Fraction *diff = subtract_fractions(f1, f2);
    assert(strcmp(diff->numerator->value, "1") == 0);
    assert(strcmp(diff->denominator->value, "6") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(diff);
    
    printf("Fraction subtraction tests passed!\n");
}

int main() {
    printf("Starting fraction tests...\n\n");
    
    test_fraction_creation();
    test_fraction_simplification();
    test_fraction_addition();
    test_fraction_multiplication();
    test_fraction_division();
    test_fraction_subtraction();
    
    printf("\nAll fraction tests passed successfully!\n");
    return 0;
} 