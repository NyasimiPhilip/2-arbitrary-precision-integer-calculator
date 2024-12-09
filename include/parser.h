   #ifndef PARSER_H
   #define PARSER_H

   #include "fraction.h"

   // Function to parse a fraction string (e.g., "1/2")
   Fraction* parse_fraction(const char* str);

   // Function to parse a logarithm string (e.g., "log2(8)")
   void parse_logarithm(const char* str, char** base_str, char** num_str);

   #endif // PARSER_H