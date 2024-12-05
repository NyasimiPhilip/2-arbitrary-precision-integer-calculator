// src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArbitraryInt.h"
#include "operations.h"
#include "fraction.h"
#include "base_conversion.h"

// Function prototypes
void print_guide();
char* read_input();
void process_input(const char *input);

int main() {
    print_guide();
    char *input;

    while(1) {
        printf("> ");
        input = read_input();
        if(!input) break;

        // Handle exit commands
        if(strcmp(input, "exit") ==0 || strcmp(input, "quit") ==0) {
            free(input);
            break;
        }

        // Handle help
        if(strcmp(input, "help") ==0) {
            print_guide();
            free(input);
            continue;
        }

        // Process input
        process_input(input);
        free(input);
    }

    printf("Exiting Arbitrary Precision Calculator.\n");
    return 0;
}

void print_guide() {
    printf("Arbitrary Precision Calculator\n");
    printf("Supported Operations:\n");
    printf(" - Addition: a + b\n");
    printf(" - Subtraction: a - b\n");
    printf(" - Multiplication: a * b\n");
    printf(" - Division: a / b\n");
    printf(" - Modulo: a %% b\n");
    printf(" - Power: a ^ b\n");
    printf(" - Factorial: a!\n");
    printf(" - Fraction Operations: a/b + c/d, etc.\n");
    printf(" - Base Conversion: to_base <num> <base>, from_base <str> <base>\n");
    printf(" - Logarithm: log<base>(value)\n");
    printf("Type 'exit' or 'quit' to terminate.\n\n");
}

char* read_input() {
    char buffer[1024];
    if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }

    // Remove trailing newline
    size_t len = strlen(buffer);
    if(len >0 && buffer[len -1] == '\n') {
        buffer[len -1] = '\0';
    }

    return strdup(buffer);
}

void process_input(const char *input) {
    // Basic parsing and evaluation
    // Placeholder: Implement a proper parser
    printf("You entered: %s\n", input);
    // To be implemented
}