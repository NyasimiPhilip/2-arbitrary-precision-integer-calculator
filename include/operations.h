/**
 * @file operations.h
 * @brief Core arithmetic operations interface
 *
 * Defines the interface for basic and advanced mathematical operations
 * on arbitrary precision integers.
 */

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "ArbitraryInt.h"

/**
 * @brief Adds two arbitrary precision integers
 * @param a First operand
 * @param b Second operand
 * @return Sum as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* add(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Subtracts two arbitrary precision integers
 * @param a First operand
 * @param b Second operand
 * @return Difference (a-b) as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* subtract(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Multiplies two arbitrary precision integers
 * @param a First operand
 * @param b Second operand
 * @return Product as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* multiply(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Divides two arbitrary precision integers
 * @param a Dividend
 * @param b Divisor
 * @param remainder Optional pointer to store remainder
 * @return Quotient as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* divide(const ArbitraryInt *a, const ArbitraryInt *b, ArbitraryInt **remainder);

/**
 * @brief Computes modulo of two arbitrary precision integers
 * @param a Dividend
 * @param b Divisor
 * @return Remainder as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* modulo(const ArbitraryInt *a, const ArbitraryInt *b);

/**
 * @brief Raises base to an exponent
 * @param base Base number
 * @param exponent Power to raise to (must be non-negative)
 * @return Result as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* power(const ArbitraryInt *base, const ArbitraryInt *exponent);

/**
 * @brief Computes factorial of a number
 * @param n Input number (must be non-negative)
 * @return n! as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* factorial(const ArbitraryInt *n);

/**
 * @brief Computes integer logarithm
 * @param num Input number (must be positive)
 * @param base Logarithm base (must be > 1)
 * @return Floor of log_base(num) as new ArbitraryInt* or NULL on error
 */
ArbitraryInt* logarithm(const ArbitraryInt *num, const ArbitraryInt *base);

/**
 * @brief Creates a deep copy of an arbitrary precision integer
 * @param num Number to copy
 * @return New copy as ArbitraryInt* or NULL on error
 */
ArbitraryInt* copy_arbitrary_int(const ArbitraryInt *num);

#endif // OPERATIONS_H
