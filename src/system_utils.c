/**
 * @file system_utils.c
 * @brief System-specific utility implementations
 *
 * Provides platform-independent implementations of system utilities
 * with specific handling for Windows and Unix-like systems.
 */

#include "system_utils.h"
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    /**
     * @brief Windows-specific screen clearing implementation
     * 
     * Uses Windows Console API to:
     * 1. Clear screen buffer
     * 2. Reset cursor position
     * 3. Flush output
     */
    void clear_screen(void) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {0, 0};
        DWORD count;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hStdOut, &csbi);
        FillConsoleOutputCharacter(hStdOut, ' ', 
            csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        SetConsoleCursorPosition(hStdOut, coord);
        system("cls");
        fflush(stdout);
    }
#else
    #include <unistd.h>
    /**
     * @brief Unix-specific screen clearing implementation
     * 
     * Uses system command and ensures output buffer is flushed
     */
    void clear_screen(void) {
        system("clear");
        fflush(stdout);
    }
#endif 