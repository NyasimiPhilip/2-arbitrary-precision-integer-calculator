/**
 * @file ArbitraryInt.h
 * @brief Core arbitrary precision integer implementation
 *
 * Provides the fundamental data structure and operations for
 * handling integers of arbitrary size. Numbers are stored as
 * strings of digits with separate sign handling.
 */

#ifndef ARBITRARYINT_H
#define ARBITRARYINT_H

#include <stdbool.h>

/**
 * @brief Structure representing an arbitrary precision integer
 */
typedef struct {
    bool is_negative;  /**< Sign flag (true if negative) */
    char *value;      /**< String of digits (null-terminated) */
} ArbitraryInt;

/**
 * @brief Creates a new arbitrary precision integer from string
 * @param str String representation of number
 * @return New ArbitraryInt* or NULL on error
 */
ArbitraryInt* create_arbitrary_int(const char *str);

/**
 * @brief Frees memory used by an arbitrary precision integer
 * @param num Number to free
 */
void free_arbitrary_int(ArbitraryInt *num);

/**
 * @brief Compares two arbitrary precision integers
 * @param a First number
 * @param b Second number
 * @return -1 if a<b, 0 if a=b, 1 if a>b
 */
int compare_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Prints an arbitrary precision integer
 * @param num Number to print
 */
void print_arbitrary_int(const ArbitraryInt *num);

// Utility Functions
ArbitraryInt* add_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);
ArbitraryInt* subtract_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);
ArbitraryInt* multiply_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);
int compare_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Internal function for adding arbitrary integers
 */
ArbitraryInt* add_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Internal function for subtracting arbitrary integers
 */
ArbitraryInt* subtract_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Internal function for multiplying arbitrary integers
 */
ArbitraryInt* multiply_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);

#endif // ARBITRARYINT_H 