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
- C compiler (GCC/MinGW for Windows, GCC/Clang for Unix)
- CMake 3.10 or higher (optional)
- Standard C library

### Building with build.c (Recommended)

The project includes a build script that automatically detects your build environment and chooses the appropriate build method. To use it:

```bash
# Compile the build script
gcc build.c -o build

# Run the build script
./build      # on Unix/Linux/Mac
./build.exe  # on Windows
```

The build script will:
1. Check if CMake is available on your system
2. If CMake is found:
   - Create a build directory
   - Generate build files using CMake
   - Build the project using CMake
3. If CMake is not found:
   - Fall back to direct GCC compilation
   - Compile all source files
   - Create the static library
   - Link the final executable
4. Run the calculator after successful build

### Manual Build Options

If you prefer to build manually, you can use either of these methods:

#### Option 1: Using CMake (if available)
```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build . --config Release

# Navigate to the Release directory
cd Release
```

#### Option 2: Direct GCC Compilation
```bash
#1 Create build directory
mkdir -p build/Release

#2 Compile source files individually
gcc -c src/ArbitraryInt.c -I./include -o build/ArbitraryInt.o
gcc -c src/base_conversion.c -I./include -o build/base_conversion.o
gcc -c src/operations.c -I./include -o build/operations.o
gcc -c src/parser.c -I./include -o build/parser.o
gcc -c src/system_utils.c -I./include -o build/system_utils.o
gcc -c src/fraction.c -I./include -o build/fraction.o

# 3. Create the static library
ar rcs build/Release/libcalculator.a build/ArbitraryInt.o build/base_conversion.o build/operations.o build/parser.o build/system_utils.o build/fraction.o

# 4. Compile and link main program
gcc src/main.c -L./build/Release -lcalculator -I./include -o build/Release/calculator

# 5. Navigate to the build directory
cd build/Release
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

### Building and Running Tests

#### Using CMake (Recommended)
```bash
# From the project root directory:

# Create and enter build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build all tests
cmake --build . --config Release

# Run all tests (from within the build directory)
ctest -C Release -V

```

#### Manual Test Compilation
```bash
# From the project root directory:

# First ensure the calculator library is built
# (Skip if you've already built it)
mkdir -p build/Release
gcc -c src/*.c -I./include -o build/*.o
ar rcs build/Release/libcalculator.a build/ArbitraryInt.o build/base_conversion.o build/operations.o build/parser.o build/system_utils.o build/fraction.o

# Create test build directory
mkdir -p build/tests

# Compile test files
gcc tests/test_arbitraryint.c -I./include -L./build/Release -lcalculator -o build/tests/test_arbitraryint
gcc tests/test_base_conversion.c -I./include -L./build/Release -lcalculator -o build/tests/test_base_conversion
gcc tests/test_operations.c -I./include -L./build/Release -lcalculator -o build/tests/test_operations
gcc tests/test_fraction.c -I./include -L./build/Release -lcalculator -o build/tests/test_fraction
gcc tests/test_parser.c -I./include -L./build/Release -lcalculator -o build/tests/test_parser
gcc tests/test_main.c -I./include -L./build/Release -lcalculator -o build/tests/test_main

# Run individual tests (from the tests directory)
cd build/tests
./test_arbitraryint
./test_base_conversion
./test_operations
./test_fraction
./test_parser
./test_main
```

Note: 
1. Make sure you've built the calculator library first before attempting to build tests
2. The CMake method will automatically handle library dependencies
3. For manual compilation, you need to build the library before building tests

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
