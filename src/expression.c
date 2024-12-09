#include "expression.h"
#include "operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 1000

static Token tokens[MAX_TOKENS];
static int token_count = 0;

static int get_operator_precedence(char op) {
    switch(op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

static bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

static void tokenize(const char* expr) {
    token_count = 0;
    char number[1024] = {0};
    int num_idx = 0;
    
    for(size_t i = 0; expr[i]; i++) {
        if(isspace(expr[i])) continue;
        
        if(isdigit(expr[i])) {
            number[num_idx++] = expr[i];
        } else {
            if(num_idx > 0) {
                number[num_idx] = '\0';
                tokens[token_count].type = TOKEN_NUMBER;
                tokens[token_count].value.number = create_arbitrary_int(number);
                token_count++;
                num_idx = 0;
            }
            
            if(expr[i] == '(') {
                tokens[token_count].type = TOKEN_LPAREN;
                token_count++;
            } else if(expr[i] == ')') {
                tokens[token_count].type = TOKEN_RPAREN;
                token_count++;
            } else if(is_operator(expr[i])) {
                tokens[token_count].type = TOKEN_OPERATOR;
                tokens[token_count].value.operator = expr[i];
                token_count++;
            }
        }
    }
    
    if(num_idx > 0) {
        number[num_idx] = '\0';
        tokens[token_count].type = TOKEN_NUMBER;
        tokens[token_count].value.number = create_arbitrary_int(number);
        token_count++;
    }
}

static ArbitraryInt* apply_operator(ArbitraryInt* a, ArbitraryInt* b, char op) {
    switch(op) {
        case '+': return add(a, b);
        case '-': return subtract(a, b);
        case '*': return multiply(a, b);
        case '/': return divide(a, b, NULL);
        case '^': return power(a, b);
        default: return NULL;
    }
}

ArbitraryInt* evaluate_pemdas(const char* expr) {
    tokenize(expr);
    
    // Stacks for operators and operands
    ArbitraryInt* values[MAX_TOKENS];
    char operators[MAX_TOKENS];
    int value_count = 0;
    int operator_count = 0;
    
    for(int i = 0; i < token_count; i++) {
        if(tokens[i].type == TOKEN_NUMBER) {
            values[value_count++] = copy_arbitrary_int(tokens[i].value.number);
        }
        else if(tokens[i].type == TOKEN_LPAREN) {
            operators[operator_count++] = '(';
        }
        else if(tokens[i].type == TOKEN_RPAREN) {
            while(operator_count > 0 && operators[operator_count-1] != '(') {
                ArbitraryInt* b = values[--value_count];
                ArbitraryInt* a = values[--value_count];
                char op = operators[--operator_count];
                values[value_count++] = apply_operator(a, b, op);
                free_arbitrary_int(a);
                free_arbitrary_int(b);
            }
            if(operator_count > 0) operator_count--; // Remove '('
        }
        else if(tokens[i].type == TOKEN_OPERATOR) {
            char op = tokens[i].value.operator;
            while(operator_count > 0 && 
                  operators[operator_count-1] != '(' &&
                  get_operator_precedence(operators[operator_count-1]) >= 
                  get_operator_precedence(op)) {
                ArbitraryInt* b = values[--value_count];
                ArbitraryInt* a = values[--value_count];
                char prev_op = operators[--operator_count];
                values[value_count++] = apply_operator(a, b, prev_op);
                free_arbitrary_int(a);
                free_arbitrary_int(b);
            }
            operators[operator_count++] = op;
        }
    }
    
    while(operator_count > 0) {
        ArbitraryInt* b = values[--value_count];
        ArbitraryInt* a = values[--value_count];
        char op = operators[--operator_count];
        values[value_count++] = apply_operator(a, b, op);
        free_arbitrary_int(a);
        free_arbitrary_int(b);
    }
    
    ArbitraryInt* result = copy_arbitrary_int(values[0]);
    free_arbitrary_int(values[0]);
    
    // Cleanup tokens
    for(int i = 0; i < token_count; i++) {
        if(tokens[i].type == TOKEN_NUMBER) {
            free_arbitrary_int(tokens[i].value.number);
        }
    }
    
    return result;
} 