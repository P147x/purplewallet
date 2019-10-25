#include "purple.hpp"

std::string promptPassword() {
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

//  CONSTRUCTORS
Purple::Purple() {
}

int Purple::run()
{
    this->config.loadConfiguration();
    this->tryLogin();
    //
    return 0;
}

bool    Purple::login()
{
    unsigned int    count;
    std::string     pass;

    count = 0;
    do {
        pass = promptPassword();
        std::cout << std::endl;
    } while (++count < 3);
    return false;
}

bool    Purple::tryLogin()
{
    if (this->config.getToken() == "")
        this->login();
    return false;
}

