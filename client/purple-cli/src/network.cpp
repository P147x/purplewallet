#include <sstream>
#include "network.hpp"
#include <nlohmann/json.hpp>
#include <bsm/audit.h>

using json = nlohmann::json;

Network::Network() {

}

void    Network::setToken(std::string token)
{
    this->_token = token;
}

std::string Network::getToken()
{
    return this->_token;
}

std::string Network::putNewPurchase(unsigned int wID, float sum, std::string comment, unsigned int debt_user)
{
    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    std::ostringstream response;
    std::string body;

    if (debt_user == 0)
        body = "wallet=" + std::to_string(wID) + "&sum=" + std::to_string(sum) + "&reason=" + comment;
    else if (debt_user > 0)
        body = "wallet=" + std::to_string(wID) + "&sum=" + std::to_string(sum) + "&reason=" + comment + "&owedBy=" + std::to_string(debt_user);
    request.setOpt(new curlpp::options::Url(hostname + "/api/v1/purchase"));
    //request.setOpt(new curlpp::options::Verbose(true));

    std::list<std::string> header;
    header.push_back("Content-Type: application/x-www-form-urlencoded");
    header.push_back("Authorization: Bearer " + getToken());

    request.setOpt(new curlpp::options::HttpHeader(header));
    request.setOpt(new curlpp::options::PostFields(body));
    request.setOpt(new curlpp::options::PostFieldSize(body.length()));

    request.setOpt(new curlpp::options::WriteStream(&response));

    request.perform();
    return std::string(response.str());
}

std::string Network::getWallet(int id)
{
    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    std::ostringstream response;


    request.setOpt(new curlpp::options::UserPwd("user:password"));
    request.setOpt(new curlpp::options::Url(hostname + "/api/v1/wallet/balance/" + std::to_string(id)));
    //request.setOpt(new curlpp::options::Verbose(true));

    std::list<std::string> header;
    header.push_back("Content-Type: application/octet-stream");
    header.push_back("Authorization: Bearer " + getToken());
    request.setOpt(new curlpp::options::HttpHeader(header));
    request.setOpt(new curlpp::options::WriteStream(&response));

    request.perform();
    return std::string(response.str());
}

std::string Network::connexion(std::string user, std::string pass)
{
    std::string token;

    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    std::ostringstream response;
    json empty_array_explicit = json::array();

    request.setOpt(new curlpp::options::Url(hostname + "/api/v1/login?username=" + user + "&password=" + pass));
    //request.setOpt(new curlpp::options::Verbose(true));

    std::list<std::string> header;
    header.push_back("Content-Type: application/octet-stream");
    request.setOpt(new curlpp::options::HttpHeader(header));
    request.setOpt(new curlpp::options::PostFields("username=" + user));
    request.setOpt(new curlpp::options::PostFields("password=" + pass));

    request.setOpt(new curlpp::options::WriteStream(&response));

    request.perform();
    std::string(response.str());
    auto j3 = json::parse(response.str());
    if (j3["code"] == 200)
        return j3["token"];
    else
        return "";
}

void Network::setHostname(std::string hostname) {
    this->hostname = hostname;
}
