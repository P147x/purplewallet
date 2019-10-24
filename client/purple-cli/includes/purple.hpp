#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "config.hpp"

#ifndef PURPLE_HPP
#define PURPLE_HPP

class Purple {
    private:
        Config      config;
        std::string passwordPrompt();
        bool        login();
    public:
        bool        tryLogin();
        int         run();
        Purple();
};

#endif //PURPLE_HPP