#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "config.hpp"

class Purple {
    private:
        Config      config;
        std::string passwordPrompt();
    public:
        bool        tryLogin();
        int         run();
        Purple();
};