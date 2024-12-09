#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create build directory
#ifdef _WIN32
    // Use Windows-specific mkdir
    if (system("mkdir build") != 0) {
#else
    // Use Unix-like mkdir with -p for intermediate directories
    if (system("mkdir -p build") != 0) {
#endif
        fprintf(stderr, "Error: Failed to create build directory.\n");
        return 1;
    }

    // Navigate into the build directory and run CMake commands
    if (system("cd build && cmake ..") != 0) {
        fprintf(stderr, "Error: Failed to generate build files.\n");
        return 1;
    }

    // Build with Release configuration
    if (system("cd build && cmake --build . --config Release") != 0) {
        fprintf(stderr, "Error: Failed to build the project.\n");
        return 1;
    }

    // Navigate to the release directory and run the executable
#ifdef _WIN32
    // Windows: use .\\ for running executables
    if (system("cd build\\Release && .\\calculator.exe") != 0) {
#else
    // Unix-like OS: use ./ for running executables
    if (system("cd build/Release && ./calculator") != 0) {
#endif
        fprintf(stderr, "Error: Failed to run the executable.\n");
        return 1;
    }

    printf("Build and execution process completed successfully.\n");
    return 0;
}
