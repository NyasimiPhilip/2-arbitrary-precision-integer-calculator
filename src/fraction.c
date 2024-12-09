/**
 * fraction.c - Fraction Operations Implementation
 * 
 * This module implements rational number arithmetic using arbitrary precision
 * integers. Features include:
 * - Automatic fraction simplification using GCD
 * - Support for improper fractions (e.g., 5/4)
 * - Basic arithmetic operations (+, -, *, /)
 * - Proper sign handling
 */

#include "fraction.h"
#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * gcd - Calculate Greatest Common Divisor
 * @a: First arbitrary integer
 * @b: Second arbitrary integer
 *
 * Uses Euclidean algorithm to find GCD for fraction simplification.
 * Handles signs by converting to absolute values first.
 *
 * Return: ArbitraryInt* containing the GCD
 */
static ArbitraryInt* gcd(const ArbitraryInt *a, const ArbitraryInt *b) {
    ArbitraryInt *temp_a = copy_arbitrary_int(a);
    ArbitraryInt *temp_b = copy_arbitrary_int(b);
    
    // Make absolute values for GCD
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

/**
 * create_fraction - Create and simplify a new fraction
 * @numerator: ArbitraryInt for numerator
 * @denominator: ArbitraryInt for denominator
 *
 * Creates a new fraction and automatically simplifies it using GCD.
 * Handles sign normalization (negative denominator case).
 *
 * Return: Pointer to new Fraction or NULL on error
 */
Fraction* create_fraction(const ArbitraryInt *numerator, const ArbitraryInt *denominator) {
    if (!numerator || !denominator || strcmp(denominator->value, "0") == 0) {
        return NULL;
    }

    Fraction *result = malloc(sizeof(Fraction));
    if (!result) return NULL;

    result->numerator = copy_arbitrary_int(numerator);
    result->denominator = copy_arbitrary_int(denominator);

    // Simplify using GCD
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

/**
 * add_fractions - Add two fractions
 * @a: First fraction
 * @b: Second fraction
 *
 * Implements (a/b + c/d) = (ad + bc)/(bd)
 * Result is automatically simplified.
 *
 * Return: Pointer to new Fraction containing sum
 */
Fraction* add_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    // (a/b + c/d) = (ad + bc)/(bd)
    ArbitraryInt *ad = multiply(a->numerator, b->denominator);
    ArbitraryInt *bc = multiply(b->numerator, a->denominator);
    ArbitraryInt *bd = multiply(a->denominator, b->denominator);

    ArbitraryInt *sum = add(ad, bc);
    Fraction *result = create_fraction(sum, bd);

    free_arbitrary_int(ad);
    free_arbitrary_int(bc);
    free_arbitrary_int(bd);
    free_arbitrary_int(sum);

    return result;
}

Fraction* subtract_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    // (a/b - c/d) = (ad - bc)/(bd)
    ArbitraryInt *ad = multiply(a->numerator, b->denominator);
    ArbitraryInt *bc = multiply(b->numerator, a->denominator);
    ArbitraryInt *bd = multiply(a->denominator, b->denominator);

    ArbitraryInt *diff = subtract(ad, bc);
    Fraction *result = create_fraction(diff, bd);

    free_arbitrary_int(ad);
    free_arbitrary_int(bc);
    free_arbitrary_int(bd);
    free_arbitrary_int(diff);

    return result;
}

Fraction* multiply_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    // (a/b * c/d) = (ac)/(bd)
    ArbitraryInt *ac = multiply(a->numerator, b->numerator);
    ArbitraryInt *bd = multiply(a->denominator, b->denominator);

    Fraction *result = create_fraction(ac, bd);

    free_arbitrary_int(ac);
    free_arbitrary_int(bd);

    return result;
}

Fraction* divide_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b || strcmp(b->numerator->value, "0") == 0) {
        return NULL;
    }

    // (a/b / c/d) = (ad)/(bc)
    ArbitraryInt *ad = multiply(a->numerator, b->denominator);
    ArbitraryInt *bc = multiply(b->numerator, a->denominator);

    Fraction *result = create_fraction(ad, bc);

    free_arbitrary_int(ad);
    free_arbitrary_int(bc);

    return result;
}

void print_fraction(const Fraction *frac) {
    if (!frac || !frac->numerator || !frac->denominator) {
        printf("Invalid fraction");
        return;
    }

    if (frac->numerator->is_negative != frac->denominator->is_negative) {
        printf("-");
    }
    printf("%s/%s", frac->numerator->value, frac->denominator->value);
}

void free_fraction(Fraction *frac) {
    if (frac) {
        free_arbitrary_int(frac->numerator);
        free_arbitrary_int(frac->denominator);
        free(frac);
    }
} 