/**
 * @file main.c
 * @brief Main REPL interface for calculator
 *
 * Implements the Read-Eval-Print Loop (REPL) for the calculator.
 * Handles:
 * - User input parsing
 * - Command execution
 * - Result display
 * - Error handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>  // For bool type
#include "operations.h"
#include "base_conversion.h"
#include "system_utils.h"
#include "parser.h"
#include "fraction.h"

#define MAX_INPUT 1024

/**
 * @brief Displays help information
 * 
 * Shows available commands and their syntax including:
 * - Basic arithmetic operations
 * - Fraction operations
 * - Base conversion
 * - Advanced operations
 */
void print_help() {
    printf("\nArbitrary Precision Calculator\n");
    printf("Available operations:\n");
    printf("  clear                Clear the screen\n");
    printf("\nBasic Arithmetic:\n");
    printf("  <num1> + <num2>      Addition\n");
    printf("  <num1> - <num2>      Subtraction\n");
    printf("  <num1> * <num2>      Multiplication\n");
    printf("  <num1> / <num2>      Division\n");
    printf("  <num1> %% <num2>     Modulo\n");
    printf("  <num1> ^ <num2>      Power\n");
    printf("\nFraction Operations:\n");
    printf("  <num1>/<den1> + <num2>/<den2>   Fraction addition\n");
    printf("  <num1>/<den1> - <num2>/<den2>   Fraction subtraction\n");
    printf("  <num1>/<den1> * <num2>/<den2>   Fraction multiplication\n");
    printf("  <num1>/<den1> / <num2>/<den2>   Fraction division\n");
    printf("\nAdvanced Operations:\n");
    printf("  <num>!                   Factorial\n");
    printf("  log<base>(<num>)         Logarithm\n");
    printf("  to_base <num> <base>     Convert to base\n");
    printf("  from_base <num> <base>   Convert from base\n");
    printf("\nOther Commands:\n");
    printf("  help\n");
    printf("  exit\n\n");
}

/**
 * @brief Main program entry point
 * 
 * Implements the REPL loop and handles:
 * 1. Input reading
 * 2. Command parsing
 * 3. Operation execution
 * 4. Result display
 * 
 * @return 0 on success, non-zero on error
 */
int main() {
    // Initialize REPL environment
    char input[MAX_INPUT];
    setbuf(stdout, NULL);  // Disable output buffering
    
    printf("Welcome to Arbitrary Precision Calculator\n");
    printf("Type 'help' for available commands or 'exit' to quit\n");
    
    while(1) {
        printf("> ");
        if(!fgets(input, MAX_INPUT, stdin)) break;
        
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;
        
        // Skip empty input
        if(strlen(input) == 0) {
            continue;
        }
        
        // Handle special commands first
        if(strcmp(input, "exit") == 0) {
            break;
        }
        if(strcmp(input, "help") == 0) {
            print_help();
            continue;
        }
        if(strcmp(input, "clear") == 0) {
            clear_screen();
            continue;
        }
        
        // Base Conversion Section - Must be before tokenization
        if(strncmp(input, "to_base", 7) == 0) {
            char *num_str, *base_str;
            if(!parse_base_conversion(input, &num_str, &base_str)) {
                printf("Usage: to_base <number> <base>\n");
                continue;
            }
            
            ArbitraryInt *num = create_arbitrary_int(num_str);
            int base = atoi(base_str);
            
            if(base < 2 || base > 36) {
                printf("Base must be between 2 and 36\n");
                free(num_str);
                free(base_str);
                free_arbitrary_int(num);
                continue;
            }
            
            char *result = to_base(num, base);
            if(result) {
                printf("%s\n", result);
                free(result);
            } else {
                printf("Base conversion failed\n");
            }
            
            free(num_str);
            free(base_str);
            free_arbitrary_int(num);
            continue;
        }
        
        if(strncmp(input, "from_base", 9) == 0) {
            char *num_str, *base_str;
            if(!parse_from_base(input, &num_str, &base_str)) {
                printf("Usage: from_base <number> <base>\n");
                continue;
            }
            
            int base = atoi(base_str);
            if(base < 2 || base > 36) {
                printf("Base must be between 2 and 36\n");
                free(num_str);
                free(base_str);
                continue;
            }
            
            ArbitraryInt *result = from_base(num_str, base);
            if(result) {
                print_arbitrary_int(result);
                printf("\n");
                free_arbitrary_int(result);
            }
            
            free(num_str);
            free(base_str);
            continue;
        }
        
        // Special handling for factorial and logarithm before tokenization
        // Remove spaces from input for factorial
        char temp_input[MAX_INPUT];
        strcpy(temp_input, input);
        char *p = temp_input;
        char *q = temp_input;
        while (*p != '\0') {
            if (*p != ' ') {
                *q = *p;
                q++;
            }
            p++;
        }
        *q = '\0';
        
        if(strchr(temp_input, '!')) {
            // Handle factorial
            char *num_str = strtok(temp_input, "!");
            if(num_str) {
                ArbitraryInt *num = create_arbitrary_int(num_str);
                ArbitraryInt *result = factorial(num);
                if(result) {
                    printf("Result: ");
                    print_arbitrary_int(result);
                    printf("\n");
                    free_arbitrary_int(result);
                }
                free_arbitrary_int(num);
            }
            continue;
        }
        
        if(strncmp(input, "log", 3) == 0 || strchr(input, '(')) {
            char *base_str, *num_str;
            parse_logarithm(input, &base_str, &num_str);
            if(!base_str || !num_str) {
                printf("Usage: log<base>(<number>) or log(<number>) for base 10\n");
                continue;
            }
            
            ArbitraryInt *base = create_arbitrary_int(base_str);
            ArbitraryInt *num = create_arbitrary_int(num_str);
            ArbitraryInt *result = logarithm(num, base);
            
            if(result) {
                printf("Result: ");
                print_arbitrary_int(result);
                printf("\n");
                free_arbitrary_int(result);
            }
            
            free(base_str);
            free(num_str);
            free_arbitrary_int(base);
            free_arbitrary_int(num);
            continue;
        }
        
        // Parse input into tokens
        char *first = strtok(input, " ");
        char *op = strtok(NULL, " ");
        char *second = strtok(NULL, " ");
        
        // Check for second operator for PEMDAS
        char *third = strtok(NULL, " ");
        char *fourth = strtok(NULL, " ");
        
        if(!first || !op || !second) {
            printf("Invalid input format\n");
            continue;
        }
        
        // Handle PEMDAS
        if(third && fourth) {
            // If second operator has higher precedence
            if((*op == '+' || *op == '-') && (*third == '*' || *third == '/' || *third == '^')) {
                // Evaluate second operation first
                ArbitraryInt *b = create_arbitrary_int(second);
                ArbitraryInt *c = create_arbitrary_int(fourth);
                ArbitraryInt *temp_result = NULL;
                
                switch(*third) {
                    case '*':
                        temp_result = multiply(b, c);
                        break;
                    case '/':
                        temp_result = divide(b, c, NULL);
                        break;
                    case '^':
                        temp_result = power(b, c);
                        break;
                }
                
                if(temp_result) {
                    // Now evaluate first operation
                    ArbitraryInt *a = create_arbitrary_int(first);
                    ArbitraryInt *final_result = NULL;
                    
                    switch(*op) {
                        case '+':
                            final_result = add(a, temp_result);
                            break;
                        case '-':
                            final_result = subtract(a, temp_result);
                            break;
                    }
                    
                    if(final_result) {
                        printf("Result: ");
                        print_arbitrary_int(final_result);
                        printf("\n");
                        free_arbitrary_int(final_result);
                    }
                    
                    free_arbitrary_int(a);
                    free_arbitrary_int(temp_result);
                }
                
                free_arbitrary_int(b);
                free_arbitrary_int(c);
                continue;
            }
        }
        
        // Fraction Arithmetic Section
        // Handles operations between two fractions
        // Supports addition, subtraction, multiplication, division
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
            switch(*op) {
                case '+':
                    result = add_fractions(f1, f2);
                    break;
                case '-':
                    result = subtract_fractions(f1, f2);
                    break;
                case '*':
                    result = multiply_fractions(f1, f2);
                    break;
                case '/':
                    result = divide_fractions(f1, f2);
                    break;
                default:
                    printf("Unsupported fraction operation: %c\n", *op);
            }
            
            if(result) {
                print_fraction(result);
                printf("\n");
                free_fraction(result);
            } else {
                printf("Error performing fraction operation\n");
            }
            
            free_fraction(f1);
            free_fraction(f2);
            continue;
        }
        
        // Regular Arithmetic Section
        // Handles operations between arbitrary precision integers
        // Includes basic and advanced operations
        ArbitraryInt *a = create_arbitrary_int(first);
        ArbitraryInt *b = create_arbitrary_int(second);
        if (!a || !b) {
            printf("Invalid number format\n");
            free_arbitrary_int(a);
            free_arbitrary_int(b);
            continue;
        }
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
            printf("\n");
            if(remainder) {
                printf("Remainder: ");
                print_arbitrary_int(remainder);
                printf("\n");
                free_arbitrary_int(remainder);
            }
            free_arbitrary_int(result);
        } else {
            printf("Operation failed\n");
        }
        
        free_arbitrary_int(a);
        free_arbitrary_int(b);
    }
    
    printf("Exiting...\n");
    return 0;
}