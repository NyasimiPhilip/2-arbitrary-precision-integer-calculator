#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/parser.h"


void test_logarithm_parser() {
    printf("Testing logarithm parser...\n");
    
    char *base_str, *num_str;
    
    // Test valid input
    parse_logarithm("log2(8)", &base_str, &num_str);
    assert(base_str != NULL);
    assert(num_str != NULL);
    assert(strcmp(base_str, "2") == 0);
    assert(strcmp(num_str, "8") == 0);
    free(base_str);
    free(num_str);
    
    // Test invalid input
    parse_logarithm("invalid", &base_str, &num_str);
    assert(base_str == NULL);
    assert(num_str == NULL);
    
    printf("Logarithm parser tests passed!\n");
}

int main() {
    printf("Starting parser tests...\n\n");
    
    test_logarithm_parser();
    
    printf("\nAll parser tests passed successfully!\n");
    return 0;
}
