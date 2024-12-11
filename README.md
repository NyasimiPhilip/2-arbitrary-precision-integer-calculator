# Arbitrary Precision Calculator

This project is an arbitrary precision calculator implemented in C. It supports operations on large integers,fractions, and base conversions without relying on any external libraries for core functionality. The calculator is wrapped in a REPL (Read-Eval-Print Loop) for interactive use.

## How It Works

The calculator uses a string-based representation for arbitrary precision integers, allowing it to handle numbers of any size (limited only by available memory). Key components include:

1. **ArbitraryInt**: Core data structure that stores numbers as strings, handling signs separately
2. **Base Conversion**: Supports conversion between bases 2-36 using digit-by-digit processing
3. **Basic Operations**: Implements arithmetic algorithms for basic operations
4. **Advanced Operations**: Includes power, factorial, and logarithm calculations
5. **Fraction Operations**: Handles rational numbers with automatic simplification


## Building the Project

### Prerequisites
- CMake 3.10 or higher (for CMake build)
- C compiler (GCC/MinGW for Windows, GCC/Clang for Unix)
- Standard C library

### Option 1: Using CMake

#### Unix/Linux/Mac:
```bash
# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build . --config Release

# Run tests from within the build directory
ctest -C Release -V
```

#### Windows (PowerShell):
```powershell
# Create and enter build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build with configuration
cmake --build . --config Release

# Run tests from within the build directory
ctest -C Release -V
```

### Option 2: Manual Compilation

#### Unix/Linux/Mac:
```bash
# Compile library
gcc -c src/*.c -I./include

# Create static library
ar rcs libcalculator.a *.o

# Compile and link main program
gcc src/main.c -L. -lcalculator -I./include -o calculator

# Compile tests
gcc tests/test_arbitraryint.c -L. -lcalculator -I./include -o test_arbitraryint
gcc tests/test_base_conversion.c -L. -lcalculator -I./include -o test_base_conversion
gcc tests/test_operations.c -L. -lcalculator -I./include -o test_operations

# Run tests
./test_arbitraryint
./test_base_conversion
./test_operations
```

#### Windows :
```powershell
# Compile library
gcc -c src/*.c -I./include

# Create static library
ar rcs libcalculator.a *.o

# Compile and link main program
gcc src/main.c -L. -lcalculator -I./include -o calculator.exe

# Compile tests
gcc tests/test_arbitraryint.c -L. -lcalculator -I./include -o test_arbitraryint.exe
gcc tests/test_base_conversion.c -L. -lcalculator -I./include -o test_base_conversion.exe
gcc tests/test_fraction.c -L. -lcalculator -I./include -o test_fraction.exe
gcc tests/test_operations.c -L. -lcalculator -I./include -o test_operations.exe

# Run tests
./test_arbitraryint.exe
./test_base_conversion.exe
./test_fraction.exe
./test_operations.exe
```

### Option 3:Use the provided build.c file in the root of the project
```bash
#Compile the program
gcc build.c -o build
```
#### Unix/Linux/Mac:
```bash
#Compile the program
./build
```

#### Windows (MinGW):
```bash
./build.exe
```

### Running the Calculator

#### Unix/Linux/Mac:
```bash
# From the build directory
./calculator
```

#### Windows:
```powershell
# From the build directory
.\calculator.exe
```

## Usage Examples

### Basic Arithmetic
```bash
> 123456789 + 987654321
1111111110
> 1000000000 - 1
999999999
> 12345 * 98765
1219253925
> 1000000 / 3
333333
Remainder: 1
```


### Fraction Arithmetic
```bash
> 1/2 + 1/3
5/6
> 3/4 - 1/6
7/12
> 2/3 * 3/4
1/2
> 3/4 / 1/2
3/2
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
### Advanced Operations
```
> 2 ^ 10
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

### Fraction Implementation
- Fractions are stored as pairs of ArbitraryInts (numerator/denominator)
- Automatic simplification using GCD (Greatest Common Divisor)
- Support for improper fractions (e.g., 5/4)
- Sign normalization (denominator is always positive)
- Operations:
  * Addition: (a/b + c/d) = (ad + bc)/(bd)
  * Subtraction: (a/b - c/d) = (ad - bc)/(bd)
  * Multiplication: (a/b * c/d) = (ac)/(bd)
  * Division: (a/b / c/d) = (ad)/(bc)

### Algorithms
- Addition/Subtraction: Digit-by-digit processing with carry/borrow
- Multiplication: Long multiplication algorithm
- Division: Long division with remainder
- Base Conversion: Repeated division method
- GCD: Euclidean algorithm for fraction simplification
- Fraction Arithmetic: Uses cross multiplication and GCD simplification

### Error Handling
- Division by zero checks
- Invalid base handling (must be 2-36)
- Memory allocation failure detection
- Invalid input format detection
- Invalid fraction format detection
- Mismatched parentheses detection
- Invalid expression syntax detection

## Testing

The project includes comprehensive test suites for:
- Basic arithmetic operations
- Base conversion
- Fraction operations and simplification
- Edge cases (very large numbers, zero, negative numbers)
- Error conditions

Run the test suite:
./test_arbitraryint
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
- Negative exponents are not supported
- Logarithms return floor values only