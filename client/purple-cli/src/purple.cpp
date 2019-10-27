#include <vector>
#include "purple.hpp"
#include "utils.h"
#include <cmath>
#include <nlohmann/json.hpp>

//  CONSTRUCTORS

void    Purple::printHelp()
{
    std::cout << "Help ? No." << std::endl;
}

void    Purple::getWalletInformation(int id)
{
    std::string wallet = this->network.getWallet(id);
    auto json = nlohmann::json::parse(wallet);
    unsigned int users;
    users = json["NbUsers"].get<int>();

    if (json["code"] >= 300)
    {
        std::cerr << "Error occured" << std::endl;
        return;
    }
    std::cout   << "=== Wallet 1 informations ===" << std::endl;
    for (int i = 0; i != users; i++)
    {
        std::cout << "User :" << json["Users"][i]["UserID"] << std::endl
                    << "Total : " << json["Users"][i]["Total"] << std::endl
                    << "Expenses informations :" << std::endl
                    << " - Commons : " << json["Users"][i]["CommonPurchases"] << std::endl
                    << " - Debts : " << json["Users"][i]["Debts"] << std::endl
                    << "Current user balance : " << json["Users"][i]["Balance"] << std::endl << std::endl;
    }

}

float   Purple::setSum()
{
    float           sum;

    std::cout << "[0f-2000f]: ";
    std::cin >> sum;
    if (sum < 0)
    {
        std::cerr << "[Error] You must enter a positive value" << std::endl;
        return 0;
    }
    return sum;
}

bool    Purple::printInvoice(unsigned int wallet, float sum, std::string comment, unsigned int debt_user)
{
    std::string    response;

    std::cout << "Please review your invoice importation before" << std::endl << std::endl;
    std::cout << "----- ~ -----" << std::endl;
    if (debt_user > 0)
    {
        std::cout << "- Type: DEBT" << std::endl;
        std::cout << "- Debt owed by ID " + std::to_string(debt_user) << std::endl;
    }
    else
        std::cout << "- Type: PURCHASE" << std::endl;
    std::cout << "- Price: " + std::to_string(sum) << std::endl << std::endl;
    while (true) {
        std::cout << "Are you sure ?" << std::endl << "[y/N]: ";
        std::cin.ignore();
        std::getline(std::cin, response);
        if (response.length() == 0 || tolower(response.c_str()[0]) == 'n')
        {
            std::cout << "Aborted" << std::endl;
            return false;
        }
        else if (tolower(response.c_str()[0]) == 'y')
            return true;
    }
}

void    Purple::addPurchase(bool isDebt)
{
    unsigned int    wallet;
    unsigned int    debt_user = 0;
    float           sum;
    std::string     comment;

    std::cout << "Enter your wallet ID" << std::endl;
    std::cout << "[0-100]: ";
    std::cin >> wallet;

    if (isDebt)
    {
        std::cout << "Who has to pay that ?" << std::endl;
        std::cout << "[User ID]: ";
        std::cin >> debt_user;
    }

    std::cout << "Enter the sum of your invoice" << std::endl;
    while ((sum = this->setSum()) == 0);

    std::cout << "Reason of your buy ?" << std::endl;
    std::cout << "[]: ";
    std::cin >> comment;

    if (this->printInvoice(wallet, sum, comment, debt_user))
        network.putNewPurchase(wallet, sum, comment, debt_user);
}

void    Purple::setHostname(std::string hostname)
{
    this->config.setHostname(hostname);
    std::cout << "Hostname set to " << hostname << std::endl;
    this->config.save();
}

void    Purple::commandPicker(std::vector<std::string> args)
{
    if(args[0] == "wallet")
    {
        std::cout << "Balance asked" << std::endl;
        this->getWalletInformation(std::stoi(args[1]));
    }
    else if(args[0] == "add")
    {
        if (args.size() == 2 && args[1] == "purchase")
            this->addPurchase(false);
        else if (args.size() == 2 && args[1] == "debt")
            this->addPurchase(true);
        else
            std::cerr << "[Error] Please precise what do you want to add." << std::endl;
    }
    else
    {
        this->printHelp();
    }
}

bool    Purple::offlineCommands(std::vector<std::string> args)
{
    if (args.size() == 1 && args[0] == "logout")
        this->logout();
    else if (args[0] == "set")
    {
        if (args.size() == 3 && args[1] == "hostname")
            this->setHostname(args[2]);
        else
        {
            std::cerr << "Please precise what you want to set" << std::endl;
        }
    }
    else
        return true;
    return false;
}

int Purple::run(std::vector<std::string> args)
{
    this->config.loadConfiguration();
    if (!this->offlineCommands(args))
        return 0;
    if (!this->config.checkConfiguration())
        return 1;
    this->network.setHostname(config.getHostname());
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

