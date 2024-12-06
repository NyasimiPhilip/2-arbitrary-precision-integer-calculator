// src/fraction.c
#include "fraction.h"
#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to compute GCD
static ArbitraryInt* gcd(const ArbitraryInt *a, const ArbitraryInt *b) {
    ArbitraryInt *temp_a = copy_arbitrary_int(a);
    ArbitraryInt *temp_b = copy_arbitrary_int(b);
    
    // Make sure both numbers are positive for GCD calculation
    temp_a->is_negative = false;
    temp_b->is_negative = false;
    
    while(strcmp(temp_b->value, "0") != 0) {
        ArbitraryInt *remainder = modulo(temp_a, temp_b);
        free_arbitrary_int(temp_a);
        temp_a = temp_b;
        temp_b = remainder;
    }
    
    free_arbitrary_int(temp_b);
    return temp_a;
}

Fraction* create_fraction(const ArbitraryInt *numerator, const ArbitraryInt *denominator) {
    if (!numerator || !denominator || strcmp(denominator->value, "0") == 0) {
        fprintf(stderr, "Error: Invalid fraction or division by zero\n");
        return NULL;
    }

    Fraction *result = malloc(sizeof(Fraction));
    if (!result) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    result->numerator = copy_arbitrary_int(numerator);
    result->denominator = copy_arbitrary_int(denominator);

    // Simplify the fraction
    ArbitraryInt *gcd_value = gcd(result->numerator, result->denominator);
    if (gcd_value) {
        ArbitraryInt *new_num = divide(result->numerator, gcd_value, NULL);
        ArbitraryInt *new_den = divide(result->denominator, gcd_value, NULL);
        
        free_arbitrary_int(result->numerator);
        free_arbitrary_int(result->denominator);
        free_arbitrary_int(gcd_value);
        
        result->numerator = new_num;
        result->denominator = new_den;
    }

    // Handle signs
    if (result->denominator->is_negative) {
        result->denominator->is_negative = false;
        result->numerator->is_negative = !result->numerator->is_negative;
    }

    return result;
}

void print_fraction(const Fraction *frac) {
    if (!frac) {
        printf("NULL\n");
        return;
    }
    if (!frac->numerator || !frac->denominator) {
        printf("Invalid\n");
        return;
    }
    // Print sign if negative
    if (frac->numerator->is_negative != frac->denominator->is_negative) {
        printf("-");
    }
    // Print absolute values
    printf("%s/%s\n", frac->numerator->value, frac->denominator->value);
}

Fraction* add_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    // First multiply the numerators by the opposite denominators
    ArbitraryInt *term1 = multiply(a->numerator, b->denominator);
    ArbitraryInt *term2 = multiply(b->numerator, a->denominator);
    
    // Add the resulting numerators
    ArbitraryInt *new_num = add(term1, term2);
    
    // Multiply the denominators
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);

    // Create the new fraction and let it handle simplification
    Fraction *result = create_fraction(new_num, new_den);

    // Clean up temporary values
    free_arbitrary_int(term1);
    free_arbitrary_int(term2);
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);

    return result;
}

Fraction* subtract_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    // Create a negative version of b
    ArbitraryInt *neg_num = copy_arbitrary_int(b->numerator);
    neg_num->is_negative = !neg_num->is_negative;
    
    // Create temporary fraction for -b
    Fraction temp_b = {
        .numerator = neg_num,
        .denominator = copy_arbitrary_int(b->denominator)
    };

    // Add a + (-b)
    Fraction *result = add_fractions(a, &temp_b);

    // Clean up
    free_arbitrary_int(temp_b.numerator);
    free_arbitrary_int(temp_b.denominator);

    return result;
}

Fraction* multiply_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    // Multiply numerators and denominators
    ArbitraryInt *new_num = multiply(a->numerator, b->numerator);
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);

    // Create new fraction and let it handle simplification
    Fraction *result = create_fraction(new_num, new_den);

    // Clean up
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);

    return result;
}

Fraction* divide_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b || strcmp(b->numerator->value, "0") == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return NULL;
    }

    // Create reciprocal of b (flip numerator and denominator)
    Fraction temp_b = {
        .numerator = copy_arbitrary_int(b->denominator),
        .denominator = copy_arbitrary_int(b->numerator)
    };

    // Multiply a * (1/b)
    Fraction *result = multiply_fractions(a, &temp_b);

    // Clean up
    free_arbitrary_int(temp_b.numerator);
    free_arbitrary_int(temp_b.denominator);

    return result;
}

void free_fraction(Fraction *frac) {
    if (frac) {
        free_arbitrary_int(frac->numerator);
        free_arbitrary_int(frac->denominator);
        free(frac);
    }
}