/**
 * @file operations.c
 * @brief Implementation of arithmetic operations
 */

#include "../include/operations.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Addition wrapper function
 */
ArbitraryInt* add(const ArbitraryInt *a, const ArbitraryInt *b) {
    if (!a || !b) return NULL;
    
    ArbitraryInt *result = malloc(sizeof(ArbitraryInt));
    if (!result) return NULL;
    
    result->is_negative = false;
    result->value = NULL;
    
    ArbitraryInt *temp = add_arbitrary_ints(a, b);
    if (temp) {
        result->is_negative = temp->is_negative;
        result->value = strdup(temp->value);
        free_arbitrary_int(temp);
    }
    
    return result;
}

ArbitraryInt* subtract(const ArbitraryInt *a, const ArbitraryInt *b) {
    return subtract_arbitrary_ints(a, b);
}

ArbitraryInt* multiply(const ArbitraryInt *a, const ArbitraryInt *b) {
    return multiply_arbitrary_ints(a, b);
}

ArbitraryInt* divide(const ArbitraryInt *a, const ArbitraryInt *b, ArbitraryInt **remainder) {
    if(strcmp(b->value, "0") == 0) {
        if(strcmp(a->value, "0") == 0) {
            // 0/0 = NaN
            fprintf(stderr, "Division by zero (NaN)\n");
            return NULL;
        } else {
            // x/0 = ±Infinity
            fprintf(stderr, "Division by zero (%sInfinity)\n", 
                   a->is_negative ? "-" : "");
            return NULL;
        }
    }

    ArbitraryInt *quotient = create_arbitrary_int("0");
    ArbitraryInt *current = copy_arbitrary_int(a);
    current->is_negative = false;
    
    ArbitraryInt *abs_b = copy_arbitrary_int(b);
    abs_b->is_negative = false;
    
    while(compare_arbitrary_ints(current, abs_b) >= 0) {
        ArbitraryInt *temp = subtract(current, abs_b);
        ArbitraryInt *new_quotient = add(quotient, create_arbitrary_int("1"));
        
        free_arbitrary_int(current);
        free_arbitrary_int(quotient);
        
        current = temp;
        quotient = new_quotient;
    }
    
    if(remainder) {
        *remainder = current;
    } else {
        free_arbitrary_int(current);
    }
    
    quotient->is_negative = (a->is_negative != b->is_negative);
    free_arbitrary_int(abs_b);
    
    return quotient;
}

ArbitraryInt* modulo(const ArbitraryInt *a, const ArbitraryInt *b) {
    ArbitraryInt *remainder;
    ArbitraryInt *quotient = divide(a, b, &remainder);
    free_arbitrary_int(quotient);
    return remainder;
}

ArbitraryInt* power(const ArbitraryInt *base, const ArbitraryInt *exponent) {
    if(exponent->is_negative) {
        fprintf(stderr, "Negative exponents not supported\n");
        return NULL;
    }
    
    ArbitraryInt *result = create_arbitrary_int("1");
    ArbitraryInt *i = create_arbitrary_int("0");
    
    while(compare_arbitrary_ints(i, exponent) < 0) {
        ArbitraryInt *temp = multiply(result, base);
        free_arbitrary_int(result);
        result = temp;
        
        ArbitraryInt *new_i = add(i, create_arbitrary_int("1"));
        free_arbitrary_int(i);
        i = new_i;
    }
    
    free_arbitrary_int(i);
    return result;
}

ArbitraryInt* factorial(const ArbitraryInt *n) {
    if(n->is_negative) {
        fprintf(stderr, "Factorial of negative number undefined\n");
        return NULL;
    }
    
    ArbitraryInt *result = create_arbitrary_int("1");
    ArbitraryInt *i = create_arbitrary_int("1");
    
    while(compare_arbitrary_ints(i, n) <= 0) {
        ArbitraryInt *temp = multiply(result, i);
        free_arbitrary_int(result);
        result = temp;
        
        ArbitraryInt *new_i = add(i, create_arbitrary_int("1"));
        free_arbitrary_int(i);
        i = new_i;
    }
    
    free_arbitrary_int(i);
    return result;
}

ArbitraryInt* copy_arbitrary_int(const ArbitraryInt *num) {
    ArbitraryInt *copy = create_arbitrary_int(num->value);
    copy->is_negative = num->is_negative;
    return copy;
}

ArbitraryInt* logarithm(const ArbitraryInt *num, const ArbitraryInt *base) {
    if(base->is_negative || num->is_negative) {
        fprintf(stderr, "Logarithm not defined for negative numbers\n");
        return NULL;
    }
    
    if(strcmp(base->value, "1") == 0 || strcmp(base->value, "0") == 0) {
        fprintf(stderr, "Invalid base for logarithm\n");
        return NULL;
    }
    
    if(strcmp(num->value, "0") == 0) {
        fprintf(stderr, "Logarithm not defined for zero\n");
        return NULL;
    }
    
    // Initialize result
    ArbitraryInt *result = create_arbitrary_int("0");
    ArbitraryInt *current = create_arbitrary_int("1");
    
    // While current <= num
    while(compare_arbitrary_ints(current, num) <= 0) {
        // Multiply current by base
        ArbitraryInt *next = multiply(current, base);
        free_arbitrary_int(current);
        current = next;
        
        // Increment result
        ArbitraryInt *new_result = add(result, create_arbitrary_int("1"));
        free_arbitrary_int(result);
        result = new_result;
    }
    
    // Adjust result since we went one step too far
    ArbitraryInt *final = subtract(result, create_arbitrary_int("1"));
    free_arbitrary_int(result);
    free_arbitrary_int(current);
    
    return final;
}
