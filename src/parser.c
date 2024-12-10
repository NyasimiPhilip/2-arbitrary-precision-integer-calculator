#define _CRT_SECURE_NO_WARNINGS

/**
 * @file parser.c
 * @brief Implementation of input parsing functionality
 *
 * Contains implementations for parsing fractions and logarithmic expressions
 * from string input. Handles whitespace, validation, and memory management.
 */

#include "parser.h"
#include "fraction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Helper function to remove leading/trailing whitespace
 * @param str String to trim
 * @return Pointer to trimmed string (same memory as input)
 */
static char* trim(char* str) {
    if (!str) return NULL;
    
    // Trim leading spaces
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) return str;  // All spaces
    
    // Trim trailing spaces
    char* end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    
    return str;
}

/**
 * @brief Implementation of fraction parsing
 * 
 * Parses strings in format "numerator/denominator". Handles:
 * - Leading/trailing whitespace
 * - Memory allocation
 * - Input validation
 * - Error conditions
 */
Fraction* parse_fraction(const char* str) {
    if (!str) return NULL;

    // Find the division symbol
    const char* slash = strchr(str, '/');
    if (!slash) return NULL;

    // Calculate lengths
    size_t num_len = slash - str;
    size_t den_len = strlen(slash + 1);

    // Allocate and copy numerator string
    char* num_str = malloc(num_len + 1);
    if (!num_str) return NULL;
    strncpy(num_str, str, num_len);
    num_str[num_len] = '\0';

    // Allocate and copy denominator string
    char* den_str = malloc(den_len + 1);
    if (!den_str) {
        free(num_str);
        return NULL;
    }
    strcpy(den_str, slash + 1);

    // Trim both strings
    char* trimmed_num = trim(num_str);
    char* trimmed_den = trim(den_str);

    // Create ArbitraryInts
    ArbitraryInt* num = create_arbitrary_int(trimmed_num);
    ArbitraryInt* den = create_arbitrary_int(trimmed_den);

    // Free temporary strings
    free(num_str);
    free(den_str);

    if (!num || !den) {
        free_arbitrary_int(num);
        free_arbitrary_int(den);
        return NULL;
    }

    // Create and return the fraction
    Fraction* result = create_fraction(num, den);

    free_arbitrary_int(num);
    free_arbitrary_int(den);

    return result;
}

/**
 * @brief Implementation of logarithm parsing
 * 
 * Parses strings in format "logB(N)" where:
 * - B is optional base (defaults to 10)
 * - N is the number
 * Handles whitespace and validation.
 */
void parse_logarithm(const char* str, char** base_str, char** num_str) {
    if (!str || !base_str || !num_str) {
        if (base_str) *base_str = NULL;
        if (num_str) *num_str = NULL;
        return;
    }
    
    // Initialize output parameters
    *base_str = NULL;
    *num_str = NULL;
    
    // Check format: "logB(N)" where B is base and N is number
    if (strncmp(str, "log", 3) != 0) {
        return;
    }
    
    // Find opening and closing parentheses
    const char* open_paren = strchr(str, '(');
    const char* close_paren = strrchr(str, ')');
    
    if (!open_paren || !close_paren || close_paren <= open_paren) {
        return;
    }
    
    // Extract base (between "log" and "(")
    size_t base_len = open_paren - (str + 3);
    if (base_len == 0) {
        // Default to base 10 if not specified
        *base_str = strdup("10");
    } else {
        *base_str = (char*)malloc(base_len + 1);
        strncpy(*base_str, str + 3, base_len);
        (*base_str)[base_len] = '\0';
    }
    
    // Extract number (between parentheses)
    size_t num_len = close_paren - open_paren - 1;
    *num_str = (char*)malloc(num_len + 1);
    strncpy(*num_str, open_paren + 1, num_len);
    (*num_str)[num_len] = '\0';
    
    // Trim both strings
    char* trimmed_base = trim(*base_str);
    char* trimmed_num = trim(*num_str);
    
    // If either string is empty after trimming, clean up and return NULL
    if (!*trimmed_base || !*trimmed_num) {
        free(*base_str);
        free(*num_str);
        *base_str = NULL;
        *num_str = NULL;
        return;
    }
}

bool parse_base_conversion(const char* str, char** num_str, char** base_str) {
    if (!str || !num_str || !base_str) return false;
    *num_str = NULL;
    *base_str = NULL;
 
    // Skip "to_base" and spaces
    const char* ptr = str + 7;  // Skip "to_base"
    while (*ptr && isspace(*ptr)) ptr++;
 
    if (!*ptr) return false;
 
    // Find end of number
    const char* end = ptr;
    while (*end && !isspace(*end)) end++;
 
    // Copy number
    size_t num_len = end - ptr;
    *num_str = malloc(num_len + 1);
    if (!*num_str) return false;
    strncpy(*num_str, ptr, num_len);
    (*num_str)[num_len] = '\0';
 
    // Skip spaces after number
    ptr = end;
    while (*ptr && isspace(*ptr)) ptr++;
 
    if (!*ptr) {
        free(*num_str);
        return false;
    }
 
    // Copy base
    *base_str = strdup(ptr);
    return true;
}

bool parse_from_base(const char* str, char** num_str, char** base_str) {
    if (!str || !num_str || !base_str) return false;
    *num_str = NULL;
    *base_str = NULL;
 
    // Skip "from_base" and spaces
    const char* ptr = str + 9;  // Skip "from_base"
    while (*ptr && isspace(*ptr)) ptr++;
 
    if (!*ptr) return false;
 
    // Find end of number
    const char* end = ptr;
    while (*end && !isspace(*end)) end++;
 
    // Copy number
    size_t num_len = end - ptr;
    *num_str = malloc(num_len + 1);
    if (!*num_str) return false;
    strncpy(*num_str, ptr, num_len);
    (*num_str)[num_len] = '\0';
 
    // Skip spaces after number
    ptr = end;
    while (*ptr && isspace(*ptr)) ptr++;
 
    if (!*ptr) {
        free(*num_str);
        return false;
    }
 
    // Copy base
    *base_str = strdup(ptr);
    return true;
}