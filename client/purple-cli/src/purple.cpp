#include <vector>
#include "purple.hpp"
#include "utils.h"
#include <cmath>

//  CONSTRUCTORS
Purple::Purple() {
}

void    Purple::getWalletInformation(int id)
{
    std::cout << this->network.getWallet(id) << std::endl;
}

void    Purple::commandPicker(std::vector<std::string> args)
{
    if(args.size() == 2 && args[0] == "wallet" && std::stoi(args[1]))
    {
        std::cout << "Balance askeed" << std::endl;
        this->getWalletInformation(std::stoi(args[1]));
    }
}

int Purple::run(std::vector<std::string> args)
{
    if (args.size() == 1 && args[0] == "logout")
    {
        this->logout();
        return 0;
    }
    this->config.loadConfiguration();
    if (!this->tryLogin())
    {
        std::cerr << "[Error] Couldn't log in." << std::endl;
        return 1;
    }
    this->commandPicker(args);
    config.save();
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

void Purple::logout()
{
    this->config.removeConfiguration();
}

bool    Purple::tryLogin()
{
    if (this->config.getToken().empty())
        this->login();
    network.setToken(config.getToken());
    return true;
}

