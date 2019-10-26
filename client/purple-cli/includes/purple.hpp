#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "config.hpp"
#include "network.hpp"

#ifndef PURPLE_HPP
#define PURPLE_HPP

class Purple {
    private:
        Config      config;
        Network     network;
        bool        login();
    public:
        bool        tryLogin();
        int         run();
        Purple();
};

#endif //PURPLE_HPP