//
// Created by Lucas on 2019-10-21.
//
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include "utils.h"

std::string promptName() {
    std::string out;
    getline(std::cin, out);
    return out;
}

// Include Windows header for Windows
#ifdef _WIN32
#include <windows.h>
#else // Include Unix headers for Unix
#include <termios.h>
#include <unistd.h>
#endif

std::string getPassword()
{
// For Windows
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
#else // For Unix
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

    std::string s;
    std::cout << "Enter password:";
    getline(std::cin, s);
    std::cout << std::endl;

// Cleanup
#ifdef _WIN32
    SetConsoleMode(hStdin, mode);
#endif
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return s;
}