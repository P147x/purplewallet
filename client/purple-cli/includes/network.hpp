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
public:
    Network();

    std::string connexion(std::string user, std::string pass);
};

#endif //NETWORK_HPP