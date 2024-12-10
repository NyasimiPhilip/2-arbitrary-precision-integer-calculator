# CMakeLists.txt - Main Build Configuration
#
# Configures the build process for the arbitrary precision calculator.
# Sets up the library, executable, and tests.

cmake_minimum_required(VERSION 3.10)
project(arbitrary_precision_calculator C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directory for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create library from source files
add_library(calculator_lib
    src/ArbitraryInt.c
    src/base_conversion.c
    src/operations.c
    src/parser.c
    src/system_utils.c
    src/fraction.c
)

# Create main executable
add_executable(calculator src/main.c)
target_link_libraries(calculator calculator_lib)

# Enable testing
enable_testing()
add_subdirectory(tests)