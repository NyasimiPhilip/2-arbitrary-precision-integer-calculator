#include "operations.h"
#include <stdlib.h>
#include <string.h>

ArbitraryInt* add(const ArbitraryInt *a, const ArbitraryInt *b) {
    return add_arbitrary_ints(a, b);
}

ArbitraryInt* subtract(const ArbitraryInt *a, const ArbitraryInt *b) {
    return subtract_arbitrary_ints(a, b);
}

ArbitraryInt* multiply(const ArbitraryInt *a, const ArbitraryInt *b) {
    return multiply_arbitrary_ints(a, b);
}

ArbitraryInt* divide(const ArbitraryInt *a, const ArbitraryInt *b, ArbitraryInt **remainder) {
    if(strcmp(b->value, "0") == 0) {
        fprintf(stderr, "Division by zero\n");
        return NULL;
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
