#include <sstream>
#include "network.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Network::Network() {

}

std::string Network::connexion(std::string user, std::string pass)
{
    std::string token;

    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    std::ostringstream response;
    json empty_array_explicit = json::array();

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
    auto j3 = json::parse(response.str());
    if (j3["code"] == 200)
        return j3["token"];
    else
        return "";
}
