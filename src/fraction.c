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
    printf("DEBUG: Creating fraction - numerator: ");
    print_arbitrary_int(numerator);
    printf(", denominator: ");
    print_arbitrary_int(denominator);
    printf("\n");

    if (!numerator || !denominator || strcmp(denominator->value, "0") == 0) {
        printf("DEBUG: Invalid input to create_fraction\n");
        fprintf(stderr, "Error: Invalid fraction or division by zero\n");
        return NULL;
    }

    Fraction *result = malloc(sizeof(Fraction));
    if (!result) {
        printf("DEBUG: Memory allocation failed for fraction\n");
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    result->numerator = copy_arbitrary_int(numerator);
    result->denominator = copy_arbitrary_int(denominator);
    printf("DEBUG: Copied numerator and denominator\n");

    // Simplify the fraction
    ArbitraryInt *gcd_value = gcd(result->numerator, result->denominator);
    printf("DEBUG: Computed GCD\n");
    if (gcd_value) {
        printf("DEBUG: GCD value: ");
        print_arbitrary_int(gcd_value);
        printf("\n");

        ArbitraryInt *new_num = divide(result->numerator, gcd_value, NULL);
        ArbitraryInt *new_den = divide(result->denominator, gcd_value, NULL);
        printf("DEBUG: Divided by GCD - new numerator: ");
        print_arbitrary_int(new_num);
        printf(", new denominator: ");
        print_arbitrary_int(new_den);
        printf("\n");
        
        free_arbitrary_int(result->numerator);
        free_arbitrary_int(result->denominator);
        free_arbitrary_int(gcd_value);
        
        result->numerator = new_num;
        result->denominator = new_den;
    }

    printf("DEBUG: Final fraction: ");
    print_fraction(result);
    printf("\n");
    return result;
}

Fraction* add_fractions(const Fraction *a, const Fraction *b) {
    printf("DEBUG: Starting fraction addition\n");
    printf("DEBUG: First fraction: ");
    print_fraction(a);
    printf("\nDEBUG: Second fraction: ");
    print_fraction(b);
    printf("\n");

    if (!a || !b) {
        printf("DEBUG: Null fraction in add_fractions\n");
        return NULL;
    }

    // Validate fraction components
    if (!a->numerator || !a->denominator || !b->numerator || !b->denominator) {
        printf("DEBUG: Invalid fraction components\n");
        return NULL;
    }

    // Step 1: ad * bc
    printf("DEBUG: Computing numerator term 1 (a.num * b.den)\n");
    ArbitraryInt *term1 = multiply(a->numerator, b->denominator);
    if (!term1) {
        printf("DEBUG: Failed to compute term1\n");
        return NULL;
    }

    printf("DEBUG: Computing numerator term 2 (b.num * a.den)\n");
    ArbitraryInt *term2 = multiply(b->numerator, a->denominator);
    if (!term2) {
        printf("DEBUG: Failed to compute term2\n");
        free_arbitrary_int(term1);
        return NULL;
    }

    printf("DEBUG: Adding numerator terms\n");
    ArbitraryInt *new_num = add(term1, term2);
    if (!new_num) {
        printf("DEBUG: Failed to add terms\n");
        free_arbitrary_int(term1);
        free_arbitrary_int(term2);
        return NULL;
    }

    printf("DEBUG: Computing common denominator\n");
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);
    if (!new_den) {
        printf("DEBUG: Failed to compute denominator\n");
        free_arbitrary_int(term1);
        free_arbitrary_int(term2);
        free_arbitrary_int(new_num);
        return NULL;
    }

    printf("DEBUG: Cleaning up intermediate results\n");
    free_arbitrary_int(term1);
    free_arbitrary_int(term2);

    printf("DEBUG: Creating result fraction\n");
    Fraction *result = create_fraction(new_num, new_den);
    if (!result) {
        printf("DEBUG: Failed to create result fraction\n");
    } else {
        printf("DEBUG: Successfully created result fraction: ");
        print_fraction(result);
        printf("\n");
    }

    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);

    return result;
}

Fraction* subtract_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    ArbitraryInt *term1 = multiply(a->numerator, b->denominator);
    ArbitraryInt *term2 = multiply(b->numerator, a->denominator);
    ArbitraryInt *new_num = subtract(term1, term2);
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);

    free_arbitrary_int(term1);
    free_arbitrary_int(term2);

    Fraction *result = create_fraction(new_num, new_den);
    
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);
    
    return result;
}

Fraction* multiply_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b) return NULL;

    ArbitraryInt *new_num = multiply(a->numerator, b->numerator);
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);

    Fraction *result = create_fraction(new_num, new_den);
    
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);

    return result;
}

Fraction* divide_fractions(const Fraction *a, const Fraction *b) {
    if (!a || !b || strcmp(b->numerator->value, "0") == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return NULL;
    }

    ArbitraryInt *new_num = multiply(a->numerator, b->denominator);
    ArbitraryInt *new_den = multiply(a->denominator, b->numerator);

    Fraction *result = create_fraction(new_num, new_den);
    
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);
    
    return result;
}

void free_fraction(Fraction *frac) {
    if (frac) {
        free_arbitrary_int(frac->numerator);
        free_arbitrary_int(frac->denominator);
        free(frac);
    }
}

void print_fraction(const Fraction *frac) {
    if (!frac) {
        printf("NULL");
        return;
    }
    if (!frac->numerator || !frac->denominator) {
        printf("Invalid");
        return;
    }
    // Print sign if negative
    if (frac->numerator->is_negative != frac->denominator->is_negative) {
        printf("-");
    }
    // Print absolute values
    printf("%s/%s", frac->numerator->value, frac->denominator->value);
}