/**
 * @file expression.h
 * @brief Expression parsing and evaluation with PEMDAS support
 *
 * This module provides functionality for parsing and evaluating mathematical
 * expressions following PEMDAS (Parentheses, Exponents, Multiplication/Division,
 * Addition/Subtraction) order of operations.
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "ArbitraryInt.h"

/**
 * @brief Token types for expression parsing
 *
 * Represents different elements that can appear in a mathematical expression.
 */
typedef enum {
    TOKEN_NUMBER,     /**< Numeric literal */
    TOKEN_OPERATOR,   /**< Mathematical operator (+, -, *, /, ^) */
    TOKEN_LPAREN,     /**< Left parenthesis */
    TOKEN_RPAREN,     /**< Right parenthesis */
    TOKEN_END         /**< End of expression marker */
} TokenType;

/**
 * @brief Token structure for parsing
 * 
 * Stores either a number or an operator as part of expression parsing.
 */
typedef struct {
    TokenType type;   /**< Type of the token */
    union {
        ArbitraryInt* number;  /**< Numeric value if TOKEN_NUMBER */
        char operator;         /**< Operator character if TOKEN_OPERATOR */
    } value;
} Token;

/**
 * @brief Evaluates a mathematical expression
 * @param expr The expression string to evaluate
 * @return Result as ArbitraryInt* or NULL on error
 */
ArbitraryInt* evaluate_pemdas(const char* expr);

/**
 * @brief Gets operator precedence level
 * @param op The operator character
 * @return Precedence level (higher means higher precedence)
 */
int get_operator_precedence(char op);

/**
 * @brief Checks if a character is a valid operator
 * @param c Character to check
 * @return true if valid operator, false otherwise
 */
bool is_operator(char c);

#endif // EXPRESSION_H 