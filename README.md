# Arbitrary Precision Calculator

This project is an arbitrary precision calculator implemented in C. It supports operations on large integers, fractions, and base conversions without relying on any external libraries for core functionality. The calculator is wrapped in a REPL (Read-Eval-Print Loop) for interactive use.

## Features

- **Arbitrary Precision Integer Operations**:
  - Addition (`add`, `+`)
  - Subtraction (`subtract`, `-`)
  - Multiplication (`multiply`, `*`)
  - Division (and remainder) (`divide`, `÷`)
  - Modulo (`modulo`, `%`)
  - Exponentiation (`power`, `^`)
  - Factorial (`factorial`, `!`)

- **Fraction Operations**:
  - Addition (`add_fractions`, `+`)
  - Multiplication (`multiply_fractions`, `*`)

- **Base Conversion**:
  - Convert numbers between different bases (2 to 36).

- **Logarithms**:
  - Calculate logarithms with arbitrary bases.
  ### Interactive Commands

- `1234567890123456789 + 9876543210987654321`: Adds two numbers.
- `99999999999999999999 - 88888888888888888888`: Subtracts the second number from the first.
- `123456789 * 987654321`: Multiplies two numbers.
- `1000000000000000 ÷ 3`: Divides the first number by the second, showing quotient and remainder.
- `2^100`: Raises the first number to the power of the second.
- `50!`: Computes the factorial of a number.
- `to_base <num> <base>`: Converts a number to the specified base.
- `from_base <num> <base>`: Converts a number from the specified base to base 10.
- `1/3 + 1/4`: Adds two fractions.
- `2/5 * 3/7`: Multiplies two fractions.
- `log2(1024)`: Calculates the logarithm of a number with base 2.

## Testing

To ensure the correctness of the implementation, run the test cases provided in the `testsuite` directory.