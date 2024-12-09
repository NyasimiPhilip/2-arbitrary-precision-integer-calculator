/**
 * build.c - Build Script for Arbitrary Precision Calculator
 *
 * Provides a simple way to build the project across different platforms.
 * Handles directory creation, CMake configuration, and build process.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create build directory with platform-specific commands
#ifdef _WIN32
    if (system("mkdir build") != 0) {
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

    // Run the executable from the correct location
#ifdef _WIN32
    if (system("cd build\\Release && .\\calculator.exe") != 0) {
#else
    if (system("cd build/Release && ./calculator") != 0) {
#endif
        fprintf(stderr, "Error: Failed to run the executable.\n");
        return 1;
    }

    printf("Build and execution process completed successfully.\n");
    return 0;
}
