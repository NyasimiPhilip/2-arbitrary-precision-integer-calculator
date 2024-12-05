// src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "operations.h"
#include "fraction.h"
#include "base_conversion.h"

#define MAX_INPUT 1024

// Helper function to parse fractions
Fraction* parse_fraction(const char* str) {
    char *copy = strdup(str);
    char *numerator = strtok(copy, "/");
    char *denominator = strtok(NULL, "/");
    
    if(!numerator || !denominator) {
        free(copy);
        return NULL;
    }
    
    ArbitraryInt *num = create_arbitrary_int(numerator);
    ArbitraryInt *den = create_arbitrary_int(denominator);
    free(copy);
    
    if(!num || !den) return NULL;
    
    Fraction *result = create_fraction(num, den);
    free_arbitrary_int(num);
    free_arbitrary_int(den);
    return result;
}

// Helper function to parse logarithm input (e.g., "log2(8)")
void parse_logarithm(const char* str, char** base_str, char** num_str) {
    // Format: log<base>(<num>)
    char *copy = strdup(str);
    *base_str = NULL;
    *num_str = NULL;
    
    // Skip "log"
    char *ptr = copy + 3;
    char *end = strchr(ptr, '(');
    if(!end) {
        free(copy);
        return;
    }
    
    *end = '\0';
    *base_str = strdup(ptr);
    
    ptr = end + 1;
    end = strchr(ptr, ')');
    if(!end) {
        free(*base_str);
        *base_str = NULL;
        free(copy);
        return;
    }
    
    *end = '\0';
    *num_str = strdup(ptr);
    
    free(copy);
}

void print_help() {
    printf("\nArbitrary Precision Calculator\n");
    printf("Available operations:\n");
    printf("  <num1> + <num2>      Addition\n");
    printf("  <num1> - <num2>      Subtraction\n");
    printf("  <num1> * <num2>      Multiplication\n");
    printf("  <num1> / <num2>      Division\n");
    printf("  <num1> %% <num2>      Modulo\n");
    printf("  <num1> ^ <num2>      Power\n");
    printf("  <num>!               Factorial\n");
    printf("  log<base>(<num>)     Logarithm\n");
    printf("  <num1>/<den1> + <num2>/<den2>    Fraction addition\n");
    printf("  <num1>/<den1> * <num2>/<den2>    Fraction multiplication\n");
    printf("  to_base <num> <base>    Convert to base\n");
    printf("  from_base <num> <base>  Convert from base\n");
    printf("  help                    Show this help\n");
    printf("  exit                    Exit calculator\n\n");
}

int main() {
    char input[MAX_INPUT];
    printf("Welcome to Arbitrary Precision Calculator\n");
    printf("Type 'help' for available commands or 'exit' to quit\n");
    
    while(1) {
        printf("> ");
        if(!fgets(input, MAX_INPUT, stdin)) break;
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Handle special commands
        if(strcmp(input, "exit") == 0) break;
        if(strcmp(input, "help") == 0) {
            print_help();
            continue;
        }
        
        // Check for base conversion commands
        if(strncmp(input, "to_base", 7) == 0) {
            char *num_str = strtok(input + 8, " ");
            char *base_str = strtok(NULL, " ");
            if(!num_str || !base_str) {
                printf("Usage: to_base <number> <base>\n");
                continue;
            }
            
            ArbitraryInt *num = create_arbitrary_int(num_str);
            int base = atoi(base_str);
            char *result = to_base(num, base);
            if(result) {
                printf("%s\n", result);
                free(result);
            }
            free_arbitrary_int(num);
            continue;
        }
        
        if(strncmp(input, "from_base", 9) == 0) {
            char *num_str = strtok(input + 10, " ");
            char *base_str = strtok(NULL, " ");
            if(!num_str || !base_str) {
                printf("Usage: from_base <number> <base>\n");
                continue;
            }
            
            int base = atoi(base_str);
            ArbitraryInt *result = from_base(num_str, base);
            if(result) {
                print_arbitrary_int(result);
                free_arbitrary_int(result);
            }
            continue;
        }
        
        // Check for logarithm
        if(strncmp(input, "log", 3) == 0) {
            char *base_str, *num_str;
            parse_logarithm(input, &base_str, &num_str);
            if(!base_str || !num_str) {
                printf("Usage: log<base>(<number>)\n");
                continue;
            }
            
            ArbitraryInt *base = create_arbitrary_int(base_str);
            ArbitraryInt *num = create_arbitrary_int(num_str);
            ArbitraryInt *result = logarithm(num, base);
            
            if(result) {
                print_arbitrary_int(result);
                free_arbitrary_int(result);
            }
            
            free(base_str);
            free(num_str);
            free_arbitrary_int(base);
            free_arbitrary_int(num);
            continue;
        }
        
        // Check for factorial
        if(strchr(input, '!')) {
            char *num_str = strtok(input, "!");
            if(!num_str) {
                printf("Usage: <number>!\n");
                continue;
            }
            
            ArbitraryInt *num = create_arbitrary_int(num_str);
            ArbitraryInt *result = factorial(num);
            
            if(result) {
                print_arbitrary_int(result);
                free_arbitrary_int(result);
            }
            
            free_arbitrary_int(num);
            continue;
        }
        
        // Parse regular operations
        char *first = strtok(input, " ");
        char *op = strtok(NULL, " ");
        char *second = strtok(NULL, " ");
        
        if(!first || !op || !second) {
            printf("Invalid input format\n");
            continue;
        }
        
        // Check for fractions
        if(strchr(first, '/') && strchr(second, '/')) {
            Fraction *f1 = parse_fraction(first);
            Fraction *f2 = parse_fraction(second);
            
            if(!f1 || !f2) {
                printf("Invalid fraction format\n");
                free_fraction(f1);
                free_fraction(f2);
                continue;
            }
            
            Fraction *result = NULL;
            if(*op == '+') {
                result = add_fractions(f1, f2);
            } else if(*op == '*') {
                result = multiply_fractions(f1, f2);
            } else {
                printf("Unsupported fraction operation\n");
            }
            
            if(result) {
                print_fraction(result);
                printf("\n");
                free_fraction(result);
            }
            
            free_fraction(f1);
            free_fraction(f2);
            continue;
        }
        
        // Regular number operations
        ArbitraryInt *a = create_arbitrary_int(first);
        ArbitraryInt *b = create_arbitrary_int(second);
        ArbitraryInt *result = NULL;
        ArbitraryInt *remainder = NULL;
        
        switch(*op) {
            case '+':
                result = add(a, b);
                break;
            case '-':
                result = subtract(a, b);
                break;
            case '*':
                result = multiply(a, b);
                break;
            case '/':
                result = divide(a, b, &remainder);
                break;
            case '%':
                result = modulo(a, b);
                break;
            case '^':
                result = power(a, b);
                break;
            default:
                printf("Unknown operator: %c\n", *op);
        }
        
        if(result) {
            print_arbitrary_int(result);
            if(remainder) {
                printf("Remainder: ");
                print_arbitrary_int(remainder);
                free_arbitrary_int(remainder);
            }
            free_arbitrary_int(result);
        }
        
        free_arbitrary_int(a);
        free_arbitrary_int(b);
    }
    
    printf("Goodbye!\n");
    return 0;
}