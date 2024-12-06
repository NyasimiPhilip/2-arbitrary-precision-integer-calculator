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
    if(strcmp(denominator->value, "0") == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return NULL;
    }

    Fraction *result = malloc(sizeof(Fraction));
    if(!result) return NULL;

    result->numerator = copy_arbitrary_int(numerator);
    result->denominator = copy_arbitrary_int(denominator);

    // Simplify the fraction
    ArbitraryInt *gcd_value = gcd(result->numerator, result->denominator);
    if(gcd_value) {
        ArbitraryInt *new_num = divide(result->numerator, gcd_value, NULL);
        ArbitraryInt *new_den = divide(result->denominator, gcd_value, NULL);
        
        free_arbitrary_int(result->numerator);
        free_arbitrary_int(result->denominator);
        free_arbitrary_int(gcd_value);
        
        result->numerator = new_num;
        result->denominator = new_den;
    }

    // Handle signs
    if(result->denominator->is_negative) {
        result->denominator->is_negative = false;
        result->numerator->is_negative = !result->numerator->is_negative;
    }

    return result;
}

Fraction* add_fractions(const Fraction *a, const Fraction *b) {
    // (a_num * b_den + b_num * a_den) / (a_den * b_den)
    ArbitraryInt *term1 = multiply(a->numerator, b->denominator);
    ArbitraryInt *term2 = multiply(b->numerator, a->denominator);
    ArbitraryInt *new_num = add(term1, term2);
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);

    free_arbitrary_int(term1);
    free_arbitrary_int(term2);

    Fraction *result = create_fraction(new_num, new_den);
    
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);
    
    return result;
}

Fraction* subtract_fractions(const Fraction *a, const Fraction *b) {
    // (a_num * b_den - b_num * a_den) / (a_den * b_den)
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
    // (a_num * b_num) / (a_den * b_den)
    ArbitraryInt *new_num = multiply(a->numerator, b->numerator);
    ArbitraryInt *new_den = multiply(a->denominator, b->denominator);

    Fraction *result = create_fraction(new_num, new_den);
    
    free_arbitrary_int(new_num);
    free_arbitrary_int(new_den);
    
    return result;
}

Fraction* divide_fractions(const Fraction *a, const Fraction *b) {
    // (a_num * b_den) / (a_den * b_num)
    if(strcmp(b->numerator->value, "0") == 0) {
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
    if(frac) {
        free_arbitrary_int(frac->numerator);
        free_arbitrary_int(frac->denominator);
        free(frac);
    }
}

void print_fraction(const Fraction *frac) {
    if(!frac) {
        printf("NULL\n");
        return;
    }
    print_arbitrary_int(frac->numerator);
    printf("/");
    print_arbitrary_int(frac->denominator);
}