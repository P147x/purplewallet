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
        Purple() = default;

    int run(std::vector<std::string> args);

    void commandPicker(std::vector<std::string> args);

    void getWalletInformation(int id);

    void logout();

    void addPurchase(bool isDebt);

    float setSum();

    bool printInvoice(unsigned int wallet, float sum, std::string comment, unsigned int debt_user);

    void setHostname();

    void printHelp();

    void setHostname(std::string hostname);

    bool offlineCommands(std::vector<std::string> args);
};

#endif //PURPLE_HPP