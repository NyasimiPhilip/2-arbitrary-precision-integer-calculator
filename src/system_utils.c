#include "system_utils.h"
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    void clear_screen(void) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {0, 0};
        DWORD count;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hStdOut, &csbi);
        FillConsoleOutputCharacter(hStdOut, ' ', 
            csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        SetConsoleCursorPosition(hStdOut, coord);
    }
#else
    #include <unistd.h>
    void clear_screen(void) {
        printf("\033[2J\033[H");
    }
#endif 