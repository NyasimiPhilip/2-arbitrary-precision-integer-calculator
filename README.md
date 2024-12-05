# Arbitrary Precision Calculator

This project is an arbitrary precision calculator implemented in C. It supports operations on large integers, fractions, and base conversions without relying on any external libraries for core functionality. The calculator is wrapped in a REPL (Read-Eval-Print Loop) for interactive use.

## How It Works

The calculator uses a string-based representation for arbitrary precision integers, allowing it to handle numbers of any size (limited only by available memory). Key components include:

1. **ArbitraryInt**: Core data structure that stores numbers as strings, handling signs separately
2. **Base Conversion**: Supports conversion between bases 2-36 using digit-by-digit processing
3. **Fraction Support**: Implements rational number arithmetic with automatic simplification
4. **Basic Operations**: Implements arithmetic algorithms for basic operations
5. **Advanced Operations**: Includes power, factorial, and logarithm calculations

## Building the Project

### Prerequisites
- CMake 3.10 or higher
- C compiler (GCC or compatible)
- Standard C library

### Building with CMake

```bash
# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run tests
ctest
```

### Running the Calculator
```bash
# From the build directory
./calculator
```

## Usage Examples

### Basic Arithmetic
```bash
> 123456789 + 987654321
1111111110
> 1000000000 - 1
999999999
> 12345 98765
1219253925
> 1000000 / 3
333333
```

### Base Conversion
```bash
> to_base 42 2
101010
> from_base 1A 16
26
> to_base 255 16
FF
```

### Fractions
```
> 1/2 + 1/3
5/6
> 2/3 * 3/4
1/2
```

### Advanced Operations
```
> 2^10
1024
> 5!
120
> log2(8)
3
```

## Implementation Details

### Number Representation
- Numbers are stored as strings of digits
- Sign is stored separately as a boolean
- Leading zeros are automatically removed
- Fractions store numerator and denominator separately

### Algorithms
- Addition/Subtraction: Digit-by-digit processing with carry/borrow
- Multiplication: Long multiplication algorithm
- Division: Long division with remainder
- Base Conversion: Repeated division method
- GCD: Euclidean algorithm for fraction simplification

### Error Handling
- Division by zero checks
- Invalid base handling (must be 2-36)
- Memory allocation failure detection
- Invalid input format detection

## Testing

The project includes comprehensive test suites for:
- Basic arithmetic operations
- Fraction arithmetic
- Base conversion
- Edge cases (very large numbers, zero, negative numbers)
- Error conditions

Run the test suite:
./test_arbitraryint
./test_fraction
./test_base_conversion
./test_operations

## Interactive Commands

The calculator supports the following command formats:
- `<num1> <op> <num2>`: Basic arithmetic operations (+, -, *, /, %, ^)
- `<num>!`: Factorial
- `log<base>(<num>)`: Logarithm
- `<num1>/<den1> <op> <num2>/<den2>`: Fraction operations
- `to_base <num> <base>`: Convert to specified base
- `from_base <num> <base>`: Convert from specified base
- `help`: Show available commands
- `exit`: Quit the calculator

## Limitations

- Memory is limited by available system resources
- Performance may degrade with very large numbers
- Decimal fractions are not supported (only rational numbers)
- Negative exponents are not supported
- Logarithms return floor values only
