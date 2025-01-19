/**
 * build_test.c - Test Build Script for Arbitrary Precision Calculator
 *
 * Provides a simple way to build and run tests across different platforms.
 * Falls back to direct gcc compilation if CMake is not available.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Check if CMake is available
bool check_cmake() {
#ifdef _WIN32
    return system("cmake --version > NUL 2>&1") == 0;
#else
    return system("cmake --version > /dev/null 2>&1") == 0;
#endif
}

// Build and run tests using direct gcc commands
int build_and_run_tests_with_gcc() {
    printf("Building tests with gcc (CMake not found)...\n");

    // 1. Create build and tests directories
#ifdef _WIN32
    system("if exist build rmdir /s /q build 2> NUL");
    if (system("mkdir build") != 0 ||
        system("mkdir build\\Release") != 0 ||
        system("mkdir build\\Release\\tests") != 0) {
#else
    system("rm -rf build");  // Remove existing build directory
    if (system("mkdir -p build/Release/tests") != 0) {
#endif
        fprintf(stderr, "Error: Failed to create build directories\n");
        return 1;
    }

    // 2. Compile source files for library
    const char *compile_cmds[] = {
        "gcc -c src/ArbitraryInt.c -I./include -o build/ArbitraryInt.o",
        "gcc -c src/base_conversion.c -I./include -o build/base_conversion.o",
        "gcc -c src/operations.c -I./include -o build/operations.o",
        "gcc -c src/parser.c -I./include -o build/parser.o",
        "gcc -c src/system_utils.c -I./include -o build/system_utils.o",
        "gcc -c src/fraction.c -I./include -o build/fraction.o"
    };

    for (size_t i = 0; i < sizeof(compile_cmds)/sizeof(compile_cmds[0]); i++) {
        printf("Running: %s\n", compile_cmds[i]);
        if (system(compile_cmds[i]) != 0) {
            fprintf(stderr, "Error: Compilation failed for command: %s\n", compile_cmds[i]);
            return 1;
        }
    }

    // 3. Create the static library
    const char *lib_cmd =
#ifdef _WIN32
        "ar rcs build\\Release\\libcalculator.a"
        " build\\ArbitraryInt.o"
        " build\\base_conversion.o"
        " build\\operations.o"
        " build\\parser.o"
        " build\\system_utils.o"
        " build\\fraction.o";
#else
        "ar rcs build/Release/libcalculator.a"
        " build/ArbitraryInt.o"
        " build/base_conversion.o"
        " build/operations.o"
        " build/parser.o"
        " build/system_utils.o"
        " build/fraction.o";
#endif

    printf("Creating static library...\n");
    if (system(lib_cmd) != 0) {
        fprintf(stderr, "Error: Library creation failed.\n");
        return 1;
    }

    // 4. Compile test files
    const char *test_files[] = {
        "test_arbitraryint",
        "test_base_conversion",
        "test_operations",
        "test_main",
        "test_parser",
        "test_fraction"
    };

    for (size_t i = 0; i < sizeof(test_files)/sizeof(test_files[0]); i++) {
        char cmd[512];
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd),
            "gcc tests/%s.c -I./include -L./build/Release -lcalculator -o build\\Release\\tests\\%s.exe",
            test_files[i], test_files[i]);
#else
        snprintf(cmd, sizeof(cmd),
            "gcc tests/%s.c -I./include -L./build/Release -lcalculator -o build/Release/tests/%s",
            test_files[i], test_files[i]);
#endif
        printf("Compiling test: %s\n", cmd);
        if (system(cmd) != 0) {
            fprintf(stderr, "Error: Test compilation failed for %s\n", test_files[i]);
            return 1;
        }
    }

    // 5. Run tests
    printf("\nRunning tests...\n\n");
    for (size_t i = 0; i < sizeof(test_files)/sizeof(test_files[0]); i++) {
        char cmd[512];
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "cd build\\Release\\tests && %s.exe", test_files[i]);
#else
        snprintf(cmd, sizeof(cmd), "cd build/Release/tests && ./%s", test_files[i]);
#endif
        printf("\n=== Running %s ===\n", test_files[i]);
        if (system(cmd) != 0) {
            fprintf(stderr, "Error: Test failed: %s\n", test_files[i]);
            return 1;
        }
    }

    printf("\nAll tests completed successfully!\n");
    return 0;
}

// Build and run tests using CMake
int build_and_run_tests_with_cmake() {
    printf("Building tests with CMake...\n");

    // Create build directory
#ifdef _WIN32
    if (system("mkdir build 2> NUL") != 0) {
#else
    if (system("mkdir -p build") != 0) {
#endif
        fprintf(stderr, "Error: Failed to create build directory.\n");
        return 1;
    }

    // Generate build files using CMake
    if (system("cd build && cmake ..") != 0) {
        fprintf(stderr, "Error: Failed to generate build files.\n");
        return 1;
    }

    // Build with Release configuration
    if (system("cd build && cmake --build . --config Release") != 0) {
        fprintf(stderr, "Error: Failed to build the project.\n");
        return 1;
    }

    // Run tests using CTest
    printf("\nRunning tests with CTest...\n");
    if (system("cd build && ctest --output-on-failure") != 0) {
        fprintf(stderr, "Error: Some tests failed.\n");
        return 1;
    }

    printf("\nAll tests completed successfully!\n");
    return 0;
}

int main() {
    printf("Starting test build process...\n\n");

    int result;
    if (check_cmake()) {
        result = build_and_run_tests_with_cmake();
    } else {
        printf("CMake not found, falling back to gcc...\n");
        result = build_and_run_tests_with_gcc();
    }

    return result;
} 