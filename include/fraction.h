#ifndef FRACTION_H
#define FRACTION_H

#include "ArbitraryInt.h"

typedef struct {
    ArbitraryInt *numerator;
    ArbitraryInt *denominator;
} Fraction;

// Constructor and destructor
Fraction* create_fraction(const ArbitraryInt *numerator, const ArbitraryInt *denominator);
void free_fraction(Fraction *frac);

// Operations
Fraction* add_fractions(const Fraction *a, const Fraction *b);
Fraction* subtract_fractions(const Fraction *a, const Fraction *b);
Fraction* multiply_fractions(const Fraction *a, const Fraction *b);
Fraction* divide_fractions(const Fraction *a, const Fraction *b);

// Utility
void print_fraction(const Fraction *frac);

#endif // FRACTION_H 