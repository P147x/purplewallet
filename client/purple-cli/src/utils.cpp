//
// Created by Lucas on 2019-10-21.
//
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

std::string passwordPrompt() {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::string s;
    std::cout << "Enter password:";
    getline(std::cin, s);
    return s;
}