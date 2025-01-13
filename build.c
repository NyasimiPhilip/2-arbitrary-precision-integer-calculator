/**
 * build.c - Build Script for Arbitrary Precision Calculator
 *
 * Provides a simple way to build the project across different platforms.
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

// Build using direct gcc commands
int build_with_gcc() {
    printf("Building with gcc (CMake not found)...\n");

    // 1. Create build directory - First remove any existing build file/directory
#ifdef _WIN32
    system("if exist build rmdir /s /q build 2> NUL");
    if (system("mkdir build") != 0 ||
        system("mkdir build\\Release") != 0) {
#else
    system("rm -rf build");  // Remove existing build file/directory
    if (system("mkdir -p build/Release") != 0) {
#endif
        fprintf(stderr, "Error: Failed to create build directories\n");
        return 1;
    }

    // 2. Compile source files individually
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

    // 4. Compile and link main program
    const char *link_cmd =
#ifdef _WIN32
        "gcc src/main.c -L./build/Release -lcalculator -I./include -o build\\Release\\calculator.exe";
#else
        "gcc src/main.c -L./build/Release -lcalculator -I./include -o build/Release/calculator";
#endif

    printf("Linking final executable...\n");
    if (system(link_cmd) != 0) {
        fprintf(stderr, "Error: Linking failed.\n");
        return 1;
    }

    // 5. Change to build directory
#ifdef _WIN32
    if (system("cd build\\Release") != 0) {
#else
    if (system("cd build/Release") != 0) {
#endif
        fprintf(stderr, "Error: Failed to change to build directory.\n");
        return 1;
    }

    printf("Build completed successfully.\n");
    return 0;
}

// Build using CMake
int build_with_cmake() {
    printf("Building with CMake...\n");

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

    printf("Build completed successfully.\n");
    return 0;
}

int main() {
    printf("Starting build process...\n");

    int result;
    if (check_cmake()) {
        result = build_with_cmake();
    } else {
        printf("CMake not found, falling back to gcc...\n");
        result = build_with_gcc();
    }

    if (result == 0) {
        // Run the executable from the correct location
#ifdef _WIN32
        if (system("cd build\\Release && .\\calculator.exe") != 0) {
#else
        if (system("cd build/Release && ./calculator") != 0) {
#endif
            fprintf(stderr, "Error: Failed to run the executable.\n");
            return 1;
        }
    }

    return result;
}
