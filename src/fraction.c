// src/fraction.c
#include "fraction.h"
#include "operations.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function to compute GCD using operations
ArbitraryInt* gcd(const ArbitraryInt *a, const ArbitraryInt *b) {
    ArbitraryInt *temp_a = copy_arbitrary_int(a);
    ArbitraryInt *temp_b = copy_arbitrary_int(b);
    ArbitraryInt *zero = create_arbitrary_int("0");
    ArbitraryInt *temp;

    while(compare_arbitrary_ints(temp_b, zero) != 0) {
        ArbitraryInt *remainder = modulo(temp_a, temp_b);
        free_arbitrary_int(temp_a);
        temp_a = temp_b;
        temp_b = remainder;
    }

    free_arbitrary_int(zero);
    return temp_a;
}

// Create Fraction and simplify
Fraction* create_fraction(const ArbitraryInt *numerator, const ArbitraryInt *denominator) {
    if(compare_arbitrary_ints(denominator, create_arbitrary_int("0")) == 0) {
        fprintf(stderr, "Denominator cannot be zero.\n");
        return NULL;
    }

    Fraction *frac = malloc(sizeof(Fraction));
    if(!frac) {
        perror("Failed to allocate memory for Fraction");
        exit(EXIT_FAILURE);
    }

    // Copy numerator and denominator to avoid mutation
    frac->numerator = copy_arbitrary_int(numerator);
    frac->denominator = copy_arbitrary_int(denominator);

    // Simplify
    ArbitraryInt *common_gcd = gcd(frac->numerator, frac->denominator);
    ArbitraryInt *new_num = divide(frac->numerator, common_gcd, NULL);
    ArbitraryInt *new_den = divide(frac->denominator, common_gcd, NULL);

    free_arbitrary_int(frac->numerator);
    free_arbitrary_int(frac->denominator);
    free_arbitrary_int(common_gcd);

    frac->numerator = new_num;
    frac->denominator = new_den;

    // Handle negative denominator
    if(frac->denominator->is_negative) {
        frac->denominator->is_negative = false;
        frac->numerator->is_negative = !frac->numerator->is_negative;
    }

    return frac;
}

void free_fraction(Fraction *frac) {
    if(frac) {
        free_arbitrary_int(frac->numerator);
        free_arbitrary_int(frac->denominator);
        free(frac);
    }
}

void print_fraction(const Fraction *frac) {
    if(frac->denominator == NULL || frac->numerator == NULL) {
        printf("Invalid Fraction\n");
        return;
    }
    print_arbitrary_int(frac->numerator);
    printf(" / ");
    print_arbitrary_int(frac->denominator);
}

// Addition
Fraction* add_fractions(const Fraction *a, const Fraction *b) {
    // (a.numerator * b.denominator) + (b.numerator * a.denominator)
    ArbitraryInt *num1 = multiply(a->numerator, b->denominator);
    ArbitraryInt *num2 = multiply(b->numerator, a->denominator);
    ArbitraryInt *sum = add(num1, num2);
    free_arbitrary_int(num1);
    free_arbitrary_int(num2);

    ArbitraryInt *common_denominator = multiply(a->denominator, b->denominator);
    Fraction *result = create_fraction(sum, common_denominator);
    free_arbitrary_int(sum);
    free_arbitrary_int(common_denominator);

    return result;
}

// Subtraction
Fraction* subtract_fractions(const Fraction *a, const Fraction *b) {
    // (a.numerator * b.denominator) - (b.numerator * a.denominator)
    ArbitraryInt *num1 = multiply(a->numerator, b->denominator);
    ArbitraryInt *num2 = multiply(b->numerator, a->denominator);
    ArbitraryInt *diff = subtract(num1, num2);
    free_arbitrary_int(num1);
    free_arbitrary_int(num2);

    ArbitraryInt *common_denominator = multiply(a->denominator, b->denominator);
    Fraction *result = create_fraction(diff, common_denominator);
    free_arbitrary_int(diff);
    free_arbitrary_int(common_denominator);

    return result;
}

// Multiplication
Fraction* multiply_fractions(const Fraction *a, const Fraction *b) {
    ArbitraryInt *new_num = multiply(a->numerator, b->numerator);
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);
    Fraction *result = create_fraction(new_num, new_den);
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);
    return result;
}

// Division
Fraction* divide_fractions(const Fraction *a, const Fraction *b) {
    // (a.numerator * b.denominator) / (a.denominator * b.numerator)
    ArbitraryInt *new_num = multiply(a->numerator, b->denominator);
    ArbitraryInt *new_den = multiply(a->denominator, b->numerator);
    // Handle division by zero
    if(compare_arbitrary_ints(new_den, create_arbitrary_int("0")) == 0) {
        fprintf(stderr, "Cannot divide by zero fraction.\n");
        free_arbitrary_int(new_num);
        free_arbitrary_int(new_den);
        return NULL;
    }
    Fraction *result = create_fraction(new_num, new_den);
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);
    return result;
}