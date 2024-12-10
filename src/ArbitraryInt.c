/**
 * @file ArbitraryInt.c
 * @brief Implementation of arbitrary precision integer operations
 *
 * Core implementation of arbitrary precision integers using string-based
 * storage. Includes basic arithmetic and utility functions.
 */

#include "ArbitraryInt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Removes leading zeros from a number string
 * @param str Input string
 * @return New string without leading zeros
 */
static char* remove_leading_zeros(const char *str) {
    while(*str == '0' && *(str+1) != '\0') {
        str++;
    }
    return _strdup(str);
}

/**
 * @brief Reverses a string in place
 * @param str String to reverse
 */
static void reverse_str(char *str) {
    int i, j;
    char temp;
    size_t len = strlen(str);
    for(i = 0, j = len -1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

/**
 * @brief Adds absolute values of two numbers
 * @param a First number
 * @param b Second number
 * @return Sum as string
 */
static char* add_absolute(const char *a, const char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t max_len = (len_a > len_b) ? len_a : len_b;
    char *result = calloc(max_len + 2, sizeof(char));
    if(!result) {
        return NULL;
    }

    int carry = 0, sum;
    int digit_a, digit_b;
    for(int i = 0; i < max_len; i++) {
        digit_a = (i < len_a) ? (a[len_a -1 -i] - '0') : 0;
        digit_b = (i < len_b) ? (b[len_b -1 -i] - '0') : 0;
        sum = digit_a + digit_b + carry;
        carry = sum / 10;
        result[i] = (sum % 10) + '0';
    }
    if(carry) {
        result[max_len] = carry + '0';
    }
    reverse_str(result);
    return result;
}

// Factory function to create ArbitraryInt from string
ArbitraryInt* create_arbitrary_int(const char *str) {
    if(str == NULL) return NULL;

    ArbitraryInt *num = malloc(sizeof(ArbitraryInt));
    if(!num) {
        return NULL;
    }

    // Initialize
    num->is_negative = false;
    num->value = NULL;

    // Handle sign
    if(str[0] == '-') {
        num->is_negative = true;
        str++;
    }

    // Validate digits
    size_t len = strlen(str);
    if (len == 0 || len > INT_MAX) {
        free(num);
        return NULL;
    }

    for(size_t i = 0; i < len; i++) {
        if(!isdigit(str[i])) {
            free(num);
            return NULL;
        }
    }

    // Remove leading zeros
    num->value = remove_leading_zeros(str);
    if (!num->value) {
        free(num);
        return NULL;
    }

    return num;
}

void free_arbitrary_int(ArbitraryInt *num) {
    if(num) {
        free(num->value);
        free(num);
    }
}

// Compare two ArbitraryInts
int compare_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b) {
    if(a->is_negative != b->is_negative) {
        return a->is_negative ? -1 : 1;
    }

    // Both are positive or both are negative
    int sign_multiplier = a->is_negative ? -1 : 1;

    size_t len_a = strlen(a->value);
    size_t len_b = strlen(b->value);

    if(len_a > len_b) {
        return 1 * sign_multiplier;
    }
    if(len_a < len_b) {
        return -1 * sign_multiplier;
    }

    // If lengths are equal, perform lexicographical comparison
    int cmp = strcmp(a->value, b->value);
    return cmp * sign_multiplier;
}

// Print ArbitraryInt
void print_arbitrary_int(const ArbitraryInt *num) {
    if (!num) {
        printf("NULL");
        return;
    }
    if (!num->value) {
        printf("Invalid");
        return;
    }
    
    if (num->is_negative) {
        printf("-");
    }
    printf("%s", num->value);
}

// Subtraction of absolute values (a >= b)
static char* subtract_absolute(const char *a, const char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char *result = calloc(len_a +1, sizeof(char)); // +1 for '\0'
    if(!result) {
        perror("Failed to allocate memory for subtraction");
        exit(EXIT_FAILURE);
    }

    int borrow = 0, diff;
    int digit_a, digit_b;
    for(int i = 0; i < len_a; i++) {
        digit_a = (len_a -1 -i >=0) ? (a[len_a -1 -i] - '0') : 0;
        digit_b = (i < len_b) ? (b[len_b -1 -i] - '0') : 0;
        diff = digit_a - digit_b - borrow;
        if(diff < 0) {
            diff +=10;
            borrow =1;
        } else {
            borrow =0;
        }
        result[i] = diff + '0';
    }

    // Remove trailing zeros
    int new_len = len_a;
    while(new_len >1 && result[new_len -1] == '0') {
        new_len--;
    }
    result[new_len] = '\0';
    reverse_str(result);
    char *trimmed = remove_leading_zeros(result);
    free(result);
    return trimmed;
}

// Addition function
ArbitraryInt* add_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b) {
    if (!a || !b || !a->value || !b->value) {
        return NULL;
    }

    ArbitraryInt *result = malloc(sizeof(ArbitraryInt));
    if(!result) {
        return NULL;
    }

    // Initialize
    result->is_negative = false;
    result->value = NULL;

    if(a->is_negative == b->is_negative) {
        // Same sign: add absolute values
        char *sum = add_absolute(a->value, b->value);
        if (!sum) {
            free(result);
            return NULL;
        }
        result->value = sum;
        result->is_negative = a->is_negative;
    } else {
        // Different signs: subtract smaller absolute from larger absolute
        int cmp = compare_arbitrary_ints(a, b);
        if(cmp == 0) {
            // Result is zero
            result->value = strdup("0");
            result->is_negative = false;
        } else if(cmp > 0) {
            // |a| > |b|
            result->value = subtract_absolute(a->value, b->value);
            result->is_negative = a->is_negative;
        } else {
            // |b| > |a|
            result->value = subtract_absolute(b->value, a->value);
            result->is_negative = b->is_negative;
        }
    }

    return result;
}

// Subtraction function (a - b)
ArbitraryInt* subtract_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b) {
    // Subtracting b is equivalent to adding (-b)
    ArbitraryInt neg_b = {
        .is_negative = !b->is_negative,
        .value = strdup(b->value)
    };

    ArbitraryInt *result = add_arbitrary_ints(a, &neg_b);

    free(neg_b.value);
    return result;
}

// Helper function for multiplication
static char* multiply_by_digit(const char *num, int digit) {
    if(digit == 0) return strdup("0");
    
    size_t len = strlen(num);
    char *result = calloc(len + 2, sizeof(char));
    if(!result) {
        perror("Failed to allocate memory for multiplication");
        exit(EXIT_FAILURE);
    }

    int carry = 0;
    for(int i = len - 1; i >= 0; i--) {
        int prod = (num[i] - '0') * digit + carry;
        result[i + 1] = (prod % 10) + '0';
        carry = prod / 10;
    }
    
    if(carry > 0) {
        result[0] = carry + '0';
    } else {
        memmove(result, result + 1, len + 1);
    }
    
    return result;
}

ArbitraryInt* multiply_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b) {
    // Handle zero multiplication
    if(strcmp(a->value, "0") == 0 || strcmp(b->value, "0") == 0) {
        return create_arbitrary_int("0");
    }

    size_t len_a = strlen(a->value);
    size_t len_b = strlen(b->value);
    
    // Initialize result as "0"
    ArbitraryInt *result = create_arbitrary_int("0");
    
    // Multiply each digit of b with a
    for(size_t i = 0; i < len_b; i++) {
        int digit = b->value[len_b - 1 - i] - '0';
        char *partial = multiply_by_digit(a->value, digit);
        
        // Add zeros at the end based on position
        for(size_t j = 0; j < i; j++) {
            size_t len = strlen(partial);
            partial = realloc(partial, len + 2);
            partial[len] = '0';
            partial[len + 1] = '\0';
        }
        
        // Add to result
        ArbitraryInt *temp = create_arbitrary_int(partial);
        ArbitraryInt *new_result = add_arbitrary_ints(result, temp);
        
        free(partial);
        free_arbitrary_int(temp);
        free_arbitrary_int(result);
        result = new_result;
    }
    
    // Set sign
    result->is_negative = (a->is_negative != b->is_negative);
    
    return result;
}

