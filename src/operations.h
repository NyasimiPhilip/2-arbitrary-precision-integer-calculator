#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "ArbitraryInt.h"

// Basic arithmetic operations
ArbitraryInt* add(const ArbitraryInt *a, const ArbitraryInt *b);
ArbitraryInt* subtract(const ArbitraryInt *a, const ArbitraryInt *b);
ArbitraryInt* multiply(const ArbitraryInt *a, const ArbitraryInt *b);
ArbitraryInt* divide(const ArbitraryInt *a, const ArbitraryInt *b, ArbitraryInt **remainder);
ArbitraryInt* modulo(const ArbitraryInt *a, const ArbitraryInt *b);

// Advanced operations
ArbitraryInt* power(const ArbitraryInt *base, const ArbitraryInt *exponent);
ArbitraryInt* factorial(const ArbitraryInt *n);
ArbitraryInt* logarithm(const ArbitraryInt *num, const ArbitraryInt *base);

// Utility functions
ArbitraryInt* copy_arbitrary_int(const ArbitraryInt *num);

#endif // OPERATIONS_H
