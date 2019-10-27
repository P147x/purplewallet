#include "purple.hpp"
#include "utils.h"

//  CONSTRUCTORS
Purple::Purple() {
}

int Purple::run()
{
    this->config.loadConfiguration();
    if (!this->tryLogin())
    {
        std::cerr << "[Error] Couldn't log in." << std::endl;
        return 1;
    }
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

bool    Purple::tryLogin()
{
    if (this->config.getToken().empty())
        this->login();
    return true;
}

