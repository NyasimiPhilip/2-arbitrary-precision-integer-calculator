#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/fraction.h"

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
    
    // Test simplification
    num = create_arbitrary_int("2");
    den = create_arbitrary_int("4");
    frac = create_fraction(num, den);
    
    assert(strcmp(frac->numerator->value, "1") == 0);
    assert(strcmp(frac->denominator->value, "2") == 0);
    
    free_fraction(frac);
    free_arbitrary_int(num);
    free_arbitrary_int(den);
    
    printf("Fraction creation tests passed!\n");
}

void test_fraction_addition() {
    printf("Testing fraction addition...\n");
    
    // 1/2 + 1/3 = 5/6
    ArbitraryInt *num1 = create_arbitrary_int("1");
    ArbitraryInt *den1 = create_arbitrary_int("2");
    ArbitraryInt *num2 = create_arbitrary_int("1");
    ArbitraryInt *den2 = create_arbitrary_int("3");
    
    Fraction *f1 = create_fraction(num1, den1);
    Fraction *f2 = create_fraction(num2, den2);
    
    Fraction *sum = add_fractions(f1, f2);
    assert(strcmp(sum->numerator->value, "5") == 0);
    assert(strcmp(sum->denominator->value, "6") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(sum);
    free_arbitrary_int(num1);
    free_arbitrary_int(den1);
    free_arbitrary_int(num2);
    free_arbitrary_int(den2);
    
    printf("Fraction addition tests passed!\n");
}

void test_fraction_multiplication() {
    printf("Testing fraction multiplication...\n");
    
    // 2/3 * 3/4 = 1/2
    ArbitraryInt *num1 = create_arbitrary_int("2");
    ArbitraryInt *den1 = create_arbitrary_int("3");
    ArbitraryInt *num2 = create_arbitrary_int("3");
    ArbitraryInt *den2 = create_arbitrary_int("4");
    
    Fraction *f1 = create_fraction(num1, den1);
    Fraction *f2 = create_fraction(num2, den2);
    
    Fraction *prod = multiply_fractions(f1, f2);
    assert(strcmp(prod->numerator->value, "1") == 0);
    assert(strcmp(prod->denominator->value, "2") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(prod);
    free_arbitrary_int(num1);
    free_arbitrary_int(den1);
    free_arbitrary_int(num2);
    free_arbitrary_int(den2);
    
    printf("Fraction multiplication tests passed!\n");
}

void test_fraction_edge_cases() {
    printf("Testing fraction edge cases...\n");
    
    // Test zero numerator
    ArbitraryInt *num = create_arbitrary_int("0");
    ArbitraryInt *den = create_arbitrary_int("5");
    Fraction *frac = create_fraction(num, den);
    assert(strcmp(frac->numerator->value, "0") == 0);
    assert(strcmp(frac->denominator->value, "1") == 0);  // Should simplify
    free_fraction(frac);
    
    // Test negative fractions
    num = create_arbitrary_int("-1");
    den = create_arbitrary_int("2");
    frac = create_fraction(num, den);
    assert(frac->numerator->is_negative == true);
    free_fraction(frac);
    
    // Test double negative (should become positive)
    num = create_arbitrary_int("-1");
    den = create_arbitrary_int("-2");
    frac = create_fraction(num, den);
    assert(frac->numerator->is_negative == false);
    assert(frac->denominator->is_negative == false);
    free_fraction(frac);
    
    free_arbitrary_int(num);
    free_arbitrary_int(den);
    printf("Fraction edge case tests passed!\n");
}

void test_fraction_operations() {
    printf("Testing complex fraction operations...\n");
    
    // Test 1/2 + 1/3 + 1/6 = 1
    ArbitraryInt *num1 = create_arbitrary_int("1");
    ArbitraryInt *den1 = create_arbitrary_int("2");
    ArbitraryInt *num2 = create_arbitrary_int("1");
    ArbitraryInt *den2 = create_arbitrary_int("3");
    ArbitraryInt *num3 = create_arbitrary_int("1");
    ArbitraryInt *den3 = create_arbitrary_int("6");
    
    Fraction *f1 = create_fraction(num1, den1);
    Fraction *f2 = create_fraction(num2, den2);
    Fraction *f3 = create_fraction(num3, den3);
    
    Fraction *sum = add_fractions(f1, f2);
    Fraction *final = add_fractions(sum, f3);
    
    assert(strcmp(final->numerator->value, "1") == 0);
    assert(strcmp(final->denominator->value, "1") == 0);
    
    free_fraction(f1);
    free_fraction(f2);
    free_fraction(f3);
    free_fraction(sum);
    free_fraction(final);
    free_arbitrary_int(num1);
    free_arbitrary_int(den1);
    free_arbitrary_int(num2);
    free_arbitrary_int(den2);
    free_arbitrary_int(num3);
    free_arbitrary_int(den3);
    
    printf("Complex fraction operations tests passed!\n");
}

int main() {
    printf("Starting fraction tests...\n\n");
    
    test_fraction_creation();
    test_fraction_addition();
    test_fraction_multiplication();
    test_fraction_edge_cases();
    test_fraction_operations();
    
    printf("\nAll fraction tests passed successfully!\n");
    return 0;
}
