#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>

#include <cstdlib>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

class Network {
private:
    std::string _token;
public:
    Network();

    std::string connexion(std::string user, std::string pass);

    std::string getWallet(int id);

    void setToken(std::string token);

    std::string getToken();

    std::string putNewPurchase(unsigned int wID, float sum, std::string comment, bool isDebt);
};

#endif //NETWORK_HPP