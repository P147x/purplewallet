#include "purple.hpp"
#include "utils.h"

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
    std::string     name;
    std::string     pass;

    count = 0;
    do {
        std::cout << "Username ?" << std::endl;
        name = promptName();
        pass = getPassword();
        std::cout << std::endl;
        config.setToken(network.connexion(name, pass));
        if (config.getToken() == "")
            std::cout << "Error" << std::endl;
    } while (config.getToken() == "" && count++ < 3);
    return false;
}

bool    Purple::tryLogin()
{
    if (this->config.getToken().empty())
        this->login();
    return false;
}

