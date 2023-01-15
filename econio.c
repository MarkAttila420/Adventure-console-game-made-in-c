#include "econio.h"


#if defined(_WIN32) || defined(_WIN64)


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <assert.h>

static WORD bgcolor = COL_BLACK;
static WORD fgcolor = COL_LIGHTGRAY;
static bool rawmode = false;

static WORD colormap[] = {
    [COL_BLACK]           = 0,
    [COL_BLUE]            = FOREGROUND_BLUE,
    [COL_GREEN]           = FOREGROUND_GREEN,
    [COL_CYAN]            = FOREGROUND_GREEN | FOREGROUND_BLUE,
    [COL_RED]             = FOREGROUND_RED,
    [COL_MAGENTA]         = FOREGROUND_RED   | FOREGROUND_BLUE,
    [COL_BROWN]           = FOREGROUND_RED   | FOREGROUND_GREEN,
    [COL_LIGHTGRAY]       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
    [COL_DARKGRAY]        = FOREGROUND_INTENSITY,
    [COL_LIGHTBLUE]       = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    [COL_LIGHTGREEN]      = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    [COL_LIGHTCYAN]       = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    [COL_LIGHTRED]        = FOREGROUND_RED   | FOREGROUND_INTENSITY,
    [COL_LIGHTMAGENTA]    = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    [COL_YELLOW]          = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    [COL_WHITE]           = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

#define STDOUT GetStdHandle(STD_OUTPUT_HANDLE)

void econio_gotoxy(int x, int y) {
    COORD dwCursorPosition;
    dwCursorPosition.X = (SHORT) x;
    dwCursorPosition.Y = (SHORT) y;
    SetConsoleCursorPosition(STDOUT, dwCursorPosition);
}

void econio_clrscr(void) {
    HANDLE hstdout = STDOUT;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hstdout, &csbi)) {
        COORD coordScreen = { 0, 0 };
        DWORD cCharsWritten;
        DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter (hstdout, ' ', dwConSize, coordScreen, &cCharsWritten);
        FillConsoleOutputAttribute (hstdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
        SetConsoleCursorPosition   (hstdout, coordScreen);
    }
}

void econio_set_title(char const *title) {
    SetConsoleTitle(title);
}

#else // defined _WIN32


#include <assert.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void econio_gotoxy(int x, int y) {
    printf("\033[%d;%dH", y+1, x+1);
}


void econio_clrscr() {
    printf("\033[2J");
    econio_gotoxy(0, 0);
}

void econio_set_title(char const *title) {
    printf("\033]2;%s\007", title);
}

#endif // defined _WIN32
