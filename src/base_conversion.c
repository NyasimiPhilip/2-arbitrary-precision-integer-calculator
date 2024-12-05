// src/base_conversion.c
#include "base_conversion.h"
#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char digits_map[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Helper: Converts a single digit character to its numerical value
static int char_to_value(char c) {
    if(c >= '0' && c <= '9') return c - '0';
    if(c >= 'A' && c <= 'Z') return 10 + (c - 'A');
    if(c >= 'a' && c <= 'z') return 10 + (c - 'a');
    return -1; // Invalid character
}

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

ArbitraryInt* from_base(const char *str, int base) {
    if(base < 2 || base > 36) {
        fprintf(stderr, "Base must be between 2 and 36.\n");
        return NULL;
    }

    // Add input validation
    if (!str || strlen(str) == 0) {
        fprintf(stderr, "Invalid empty input\n");
        return NULL;
    }

    bool is_negative = false;
    size_t start = 0;
    if(str[0] == '-') {
        is_negative = true;
        start = 1;
    }

    // Create base number correctly
    char base_str[20];
    sprintf(base_str, "%d", base);
    ArbitraryInt *base_num = create_arbitrary_int(base_str);
    ArbitraryInt *result = create_arbitrary_int("0");

    // Process each digit
    for(size_t i = start; i < strlen(str); i++) {
        int val = char_to_value(str[i]);
        if(val < 0 || val >= base) {
            fprintf(stderr, "Invalid character '%c' for base %d\n", str[i], base);
            free_arbitrary_int(result);
            free_arbitrary_int(base_num);
            return NULL;
        }

        // result = result * base + val
        ArbitraryInt *mult = multiply(result, base_num);
        char val_str[2] = {0};
        sprintf(val_str, "%d", val);
        ArbitraryInt *val_ai = create_arbitrary_int(val_str);
        ArbitraryInt *new_result = add(mult, val_ai);

        free_arbitrary_int(result);
        free_arbitrary_int(mult);
        free_arbitrary_int(val_ai);
        result = new_result;
    }

    free_arbitrary_int(base_num);

    if(is_negative) {
        result->is_negative = true;
    }

    return result;
}