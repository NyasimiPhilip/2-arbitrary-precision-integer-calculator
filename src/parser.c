#include "parser.h"
#include "fraction.h"
#include <string.h>
#include <stdlib.h>

Fraction* parse_fraction(const char* str) {
    if (str == NULL) return NULL;
    
    char* slash = strchr(str, '/');
    if (slash == NULL) return NULL;
    
    // Add debug print
    printf("Debug: Parsing fraction: %s\n", str);
    
    // Split the string at the slash
    size_t num_len = slash - str;
    char* num_str = (char*)malloc(num_len + 1);
    if (!num_str) {
        printf("Debug: Memory allocation failed for numerator\n");
        return NULL;
    }
    strncpy(num_str, str, num_len);
    num_str[num_len] = '\0';
    
    // Get denominator string
    const char* den_str = slash + 1;
    
    // Create ArbitraryInts
    ArbitraryInt* num = create_arbitrary_int(num_str);
    ArbitraryInt* den = create_arbitrary_int(den_str);
    
    free(num_str);
    
    if (!num || !den) {
        printf("Debug: Failed to create ArbitraryInt\n");
        free_arbitrary_int(num);
        free_arbitrary_int(den);
        return NULL;
    }
    
    return create_fraction(num, den);
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