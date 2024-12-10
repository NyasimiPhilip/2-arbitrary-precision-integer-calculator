/**
 * @file fraction.h
 * @brief Arbitrary precision fraction operations
 *
 * This module provides support for rational number arithmetic using
 * arbitrary precision integers. All fractions are automatically
 * simplified using GCD.
 */

#ifndef FRACTION_H
#define FRACTION_H

#include "ArbitraryInt.h"

/**
 * @brief Structure representing a rational number
 * 
 * Stores a fraction as a pair of arbitrary precision integers.
 * Maintains the invariant that denominator is always positive.
 */
typedef struct {
    ArbitraryInt *numerator;    /**< Top number of fraction */
    ArbitraryInt *denominator;  /**< Bottom number of fraction */
} Fraction;

/**
 * @brief Creates a new fraction and simplifies it
 * @param numerator Top number
 * @param denominator Bottom number (must not be zero)
 * @return New Fraction* or NULL on error
 */
Fraction* create_fraction(const ArbitraryInt *numerator, const ArbitraryInt *denominator);

/**
 * @brief Frees memory used by a fraction
 * @param frac Fraction to free
 */
void free_fraction(Fraction *frac);

/**
 * @brief Adds two fractions
 * @param a First fraction
 * @param b Second fraction
 * @return Result as new Fraction* or NULL on error
 * 
 * Implements (a/b + c/d) = (ad + bc)/(bd)
 */
Fraction* add_fractions(const Fraction *a, const Fraction *b);

/**
 * @brief Subtract two fractions
 */
Fraction* subtract_fractions(const Fraction *a, const Fraction *b);

/**
 * @brief Multiply two fractions
 */
Fraction* multiply_fractions(const Fraction *a, const Fraction *b);

/**
 * @brief Divide two fractions
 */
Fraction* divide_fractions(const Fraction *a, const Fraction *b);

/**
 * @brief Print a fraction
 */
void print_fraction(const Fraction *frac);

#endif // FRACTION_H