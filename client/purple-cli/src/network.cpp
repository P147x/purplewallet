#include <sstream>
#include "network.hpp"

Network::Network() {

}

std::string Network::connexion(std::string user, std::string pass)
{
    std::string token;

    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    std::ostringstream response;

    request.setOpt(new curlpp::options::Url("localhost:8080/api/v1/login?username=" + user + "&password=" + pass));
    //request.setOpt(new curlpp::options::Verbose(true));

    std::list<std::string> header;
    header.push_back("Content-Type: application/octet-stream");
    request.setOpt(new curlpp::options::HttpHeader(header));
    request.setOpt(new curlpp::options::PostFields("username=" + user));
    request.setOpt(new curlpp::options::PostFields("password=" + pass));

    request.setOpt(new curlpp::options::WriteStream(&response));

    request.perform();
    std::string(response.str());
    std::cout << response.str();

    return token;
}
