#include "parser.h"
#include "fraction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Fraction* parse_fraction(const char* str) {
    printf("DEBUG: Starting parse_fraction with input: %s\n", str);
    if (!str) {
        printf("DEBUG: Input string is NULL\n");
        return NULL;
    }
    
    char* input = strdup(str);
    printf("DEBUG: Copied input string: %s\n", input);
    if (!input) {
        printf("DEBUG: Failed to allocate memory for input copy\n");
        return NULL;
    }
    
    char* slash = strchr(input, '/');
    if (!slash) {
        printf("DEBUG: No slash found in input\n");
        free(input);
        return NULL;
    }
    
    *slash = '\0';
    char* num_str = input;
    char* den_str = slash + 1;
    printf("DEBUG: Split into numerator: %s, denominator: %s\n", num_str, den_str);
    
    ArbitraryInt* num = create_arbitrary_int(num_str);
    ArbitraryInt* den = create_arbitrary_int(den_str);
    printf("DEBUG: Created ArbitraryInts - num: %p, den: %p\n", (void*)num, (void*)den);
    
    free(input);
    
    if (!num || !den) {
        printf("DEBUG: Failed to create ArbitraryInts\n");
        free_arbitrary_int(num);
        free_arbitrary_int(den);
        return NULL;
    }
    
    Fraction* result = create_fraction(num, den);
    printf("DEBUG: Created fraction: %p\n", (void*)result);
    
    free_arbitrary_int(num);
    free_arbitrary_int(den);
    
    return result;
}

void parse_logarithm(const char* str, char** base_str, char** num_str) {
    if (!str || !base_str || !num_str) {
        *base_str = NULL;
        *num_str = NULL;
        return;
    }
    
    // Check format: "logB(N)" where B is base and N is number
    if (strncmp(str, "log", 3) != 0) {
        *base_str = NULL;
        *num_str = NULL;
        return;
    }
    
    // Extract base
    const char* base_start = str + 3;
    const char* open_paren = strchr(base_start, '(');
    if (!open_paren) {
        *base_str = NULL;
        *num_str = NULL;
        return;
    }
    
    // Get base string
    size_t base_len = open_paren - base_start;
    *base_str = (char*)malloc(base_len + 1);
    strncpy(*base_str, base_start, base_len);
    (*base_str)[base_len] = '\0';
    
    // Get number string
    const char* num_start = open_paren + 1;
    const char* close_paren = strchr(num_start, ')');
    if (!close_paren) {
        free(*base_str);
        *base_str = NULL;
        *num_str = NULL;
        return;
    }
    
    size_t num_len = close_paren - num_start;
    *num_str = (char*)malloc(num_len + 1);
    strncpy(*num_str, num_start, num_len);
    (*num_str)[num_len] = '\0';
}