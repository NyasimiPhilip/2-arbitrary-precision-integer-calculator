#ifndef ARBITRARYINT_H
#define ARBITRARYINT_H

#include <stdbool.h>

typedef struct {
    bool is_negative;
    char *value; // Digits as a null-terminated string
} ArbitraryInt;

// Constructor
ArbitraryInt* create_arbitrary_int(const char *str);

// Destructor
void free_arbitrary_int(ArbitraryInt *num);

// Utility Functions
ArbitraryInt* add_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);
ArbitraryInt* subtract_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);
ArbitraryInt* multiply_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);
int compare_arbitrary_ints(const ArbitraryInt *a, const ArbitraryInt *b);

// Debugging
void print_arbitrary_int(const ArbitraryInt *num);

#endif // ARBITRARYINT_H
