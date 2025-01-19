/**
 * @file base_conversion.c
 * @brief Implementation of number base conversion
 *
 * Provides functionality to convert numbers between different bases (2-36).
 * Supports both to_base (decimal to target base) and from_base (source base to decimal).
 */

#include "base_conversion.h"
#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** Lookup table for digit characters (0-9, A-Z) */
static const char digits_map[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/**
 * @brief Converts a single character to its numerical value
 * @param c Character to convert
 * @return Numerical value (0-35) or -1 if invalid
 */
int char_to_value(char c) {
    int val = -1;
    
    // Handle decimal digits
    if (c >= '0' && c <= '9') {
        val = c - '0';
    }
    // Handle uppercase hex digits
    else if (c >= 'A' && c <= 'F') {
        val = 10 + (c - 'A');
    }
    // Handle lowercase hex digits
    else if (c >= 'a' && c <= 'f') {
        val = 10 + (c - 'a');
    }
    
    // Debug output
    printf("Converting '%c' to value: %d\n", c, val);
    return val;
}

/**
 * @brief Converts a decimal number to specified base
 * @param num Number to convert
 * @param base Target base (2-36)
 * @return String representation in target base or NULL on error
 */
char* to_base(const ArbitraryInt *num, int base) {
    if(base < 2 || base > 36) {
        fprintf(stderr, "Base must be between 2 and 36.\n");
        return NULL;
    }

    if(strcmp(num->value, "0") == 0) {
        return strdup("0");
    }

    bool is_negative = num->is_negative;
    ArbitraryInt *temp = copy_arbitrary_int(num);
    temp->is_negative = false;

    char *result = malloc(1000);
    int pos = 0;

    ArbitraryInt *base_ai = create_arbitrary_int("0");
    char base_str[20];
    sprintf(base_str, "%d", base);
    free_arbitrary_int(base_ai);
    base_ai = create_arbitrary_int(base_str);

    while(strcmp(temp->value, "0") != 0) {
        ArbitraryInt *remainder;
        ArbitraryInt *quotient = divide(temp, base_ai, &remainder);
        
        int rem_val = atoi(remainder->value);
        result[pos++] = digits_map[rem_val];
        
        free_arbitrary_int(temp);
        free_arbitrary_int(remainder);
        temp = quotient;
    }

    free_arbitrary_int(temp);
    free_arbitrary_int(base_ai);

    if(is_negative) {
        result[pos++] = '-';
    }
    result[pos] = '\0';
    
    // Reverse the string
    for(int i = 0; i < pos/2; i++) {
        char tmp = result[i];
        result[i] = result[pos-1-i];
        result[pos-1-i] = tmp;
    }

    return result;
}

/**
 * @brief Converts a number from specified base to decimal
 * @param str String representation in source base
 * @param base Source base (2-36)
 * @return Decimal ArbitraryInt* or NULL on error
 */
ArbitraryInt* from_base(const char *str, int base) {
    printf("Converting string '%s' from base %d\n", str, base);
    
    if (!str || base < 2 || base > 36) {
        printf("Invalid input: str=%p, base=%d\n", (void*)str, base);
        return NULL;
    }

    // Handle empty string
    if (strlen(str) == 0) {
        printf("Empty string input\n");
        return NULL;
    }

    // Handle negative numbers
    bool is_negative = false;
    if (str[0] == '-') {
        is_negative = true;
        str++;  // Skip the minus sign
        printf("Negative number detected, processing: %s\n", str);
    }

    // Create result starting at 0
    ArbitraryInt *result = create_arbitrary_int("0");
    if (!result) {
        printf("Failed to create initial result\n");
        return NULL;
    }

    // Create base number for multiplication
    char base_str[20];
    sprintf(base_str, "%d", base);
    ArbitraryInt *base_num = create_arbitrary_int(base_str);
    if (!base_num) {
        printf("Failed to create base number\n");
        free_arbitrary_int(result);
        return NULL;
    }

    // Process each digit
    for (const char *p = str; *p; p++) {
        printf("Processing digit: '%c'\n", *p);
        
        // Convert character to value
        int val = char_to_value(*p);
        if (val < 0 || val >= base) {
            printf("Invalid digit '%c' for base %d (val=%d)\n", *p, base, val);
            free_arbitrary_int(result);
            free_arbitrary_int(base_num);
            return NULL;
        }

        // result = result * base + val
        ArbitraryInt *temp = multiply(result, base_num);
        if (!temp) {
            free_arbitrary_int(result);
            free_arbitrary_int(base_num);
            return NULL;
        }

        // Convert val to ArbitraryInt
        char val_str[20];
        sprintf(val_str, "%d", val);
        ArbitraryInt *val_num = create_arbitrary_int(val_str);
        if (!val_num) {
            free_arbitrary_int(temp);
            free_arbitrary_int(base_num);
            free_arbitrary_int(result);
            return NULL;
        }

        // Add the value
        ArbitraryInt *new_result = add(temp, val_num);
        free_arbitrary_int(temp);
        free_arbitrary_int(val_num);
        free_arbitrary_int(result);
        
        if (!new_result) {
            free_arbitrary_int(base_num);
            return NULL;
        }
        
        result = new_result;
    }

    free_arbitrary_int(base_num);
    result->is_negative = is_negative;
    return result;
}