#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to trim whitespace
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