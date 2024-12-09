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
#include "operations.h"
#include "base_conversion.h"
#include "system_utils.h"
#include "parser.h"
#include "fraction.h"
#include "expression.h"

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
    printf("Basic Arithmetic:\n");
    printf("  <num1> + <num2>      Addition\n");
    printf("  <num1> - <num2>      Subtraction\n");
    printf("  <num1> * <num2>      Multiplication\n");
    printf("  <num1> / <num2>      Division\n");
    printf("  <num1> %% <num2>     Modulo\n");
    printf("  <num1> ^ <num2>      Power\n");
    printf("Fraction Operations:\n");
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
    printf("Welcome to Arbitrary Precision Calculator\n");
    printf("Type 'help' for available commands or 'exit' to quit\n");
    
    // REPL Main Loop
    // Handles input processing in the following order:
    // 1. Special commands (exit, help, clear)
    // 2. Base conversion commands
    // 3. Logarithm expressions
    // 4. Factorial operations
    // 5. Fraction operations
    // 6. Regular arithmetic operations
    while(1) {
        printf("> ");
        if(!fgets(input, MAX_INPUT, stdin)) break;
        
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;
        
        // Handle special commands first, before any tokenization
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
        
        // Parse input into tokens
        char *first = strtok(input, " ");
        char *op = strtok(NULL, " ");
        char *second = strtok(NULL, " ");
        
        if(!first || !op || !second) {
            printf("Invalid input format\n");
            continue;
        }
        
        // Base Conversion Section
        // Handles both to_base and from_base commands
        // Supports bases 2-36 using digits and letters
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
        
        // Logarithm Section
        // Parses and evaluates logarithmic expressions
        // Format: logB(N) where B is base and N is number
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
                printf("\n");
                free_arbitrary_int(result);
            }
            
            free(base_str);
            free(num_str);
            free_arbitrary_int(base);
            free_arbitrary_int(num);
            continue;
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
        }
        
        free_arbitrary_int(a);
        free_arbitrary_int(b);
        
        // Parse input
        if(strchr(input, '(') || strchr(input, ')')) {
            ArbitraryInt* result = evaluate_pemdas(input);
            if(result) {
                print_arbitrary_int(result);
                printf("\n");
                free_arbitrary_int(result);
            }
            continue;
        }
    }
    
    printf("Exiting...\n");
    return 0;
}