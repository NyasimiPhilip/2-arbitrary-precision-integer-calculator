/**
 * @file parser.h
 * @brief Input parsing functionality
 *
 * Provides functions for parsing different input formats including
 * fractions and logarithmic expressions.
 */

#ifndef PARSER_H
#define PARSER_H

#include "fraction.h"

/**
 * @brief Parses a fraction from string input
 * @param str Input string in format "numerator/denominator"
 * @return Pointer to new Fraction or NULL on error
 */
Fraction* parse_fraction(const char* str);

/**
 * @brief Parses a logarithm expression
 * @param str Input string in format "logB(N)"
 * @param base_str Output parameter for base string
 * @param num_str Output parameter for number string
 * 
 * Extracts base and number from logarithm expression.
 * If base is not specified, defaults to base 10.
 */
void parse_logarithm(const char* str, char** base_str, char** num_str);

/**
 * @brief Parses a base conversion command
 * @param str Input string in format "to_base <number> <base>"
 * @param num_str Output parameter for number string
 * @param base_str Output parameter for base string
 * @return true if parsing successful, false otherwise
 */
bool parse_base_conversion(const char* str, char** num_str, char** base_str);

/**
 * @brief Parses a from_base conversion command
 * @param str Input string in format "from_base <number> <base>"
 * @param num_str Output parameter for number string
 * @param base_str Output parameter for base string
 * @return true if parsing successful, false otherwise
 */
bool parse_from_base(const char* str, char** num_str, char** base_str);

#endif // PARSER_H