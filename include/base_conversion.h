// src/base_conversion.h
#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H

#include "ArbitraryInt.h"

// Converts ArbitraryInt to a string representation in the specified base
char* to_base(const ArbitraryInt *num, int base);

// Converts a string in the specified base to ArbitraryInt
ArbitraryInt* from_base(const char *str, int base);

// Helper function to convert a single character to its numerical value
int char_to_value(char c);

#endif // BASE_CONVERSION_H