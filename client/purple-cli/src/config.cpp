#include "config.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <sys/stat.h>
#include <fstream>
#include <nlohmann/json.hpp>

#define CONFIG_FILE "/.config/purplewallet"

Config::Config()
{
    _home = getenv("HOME");
    _home += CONFIG_FILE;
}

/*
 *  Get ? Set !
 */

std::string Config::getToken()
{
    return this->token;
}

void        Config::setToken(std::string token)
{
    this->token = token;
}

// TODO 24/10/2019 : check if folder has been created
void    Config::createConfigurationFile()
{
    mkdir(_home.c_str(), 0777);
    std::ofstream outfile;

    outfile.close();
}

void    Config::removeConfiguration()
{
    std::string     cfile = _home + "/config";

    remove(cfile.c_str());
}

void    Config::save()
{
    std::ofstream file;
    nlohmann::json j;

    file.open(_home + "/config", std::ofstream::out | std::ofstream::trunc);
    j["token"] = token;
    j["host"] = host;
    file << j;
    file.close();
}

// TODO 24/10/2019 : change printf for std::cout ffs.
bool    Config::checkConfigurationPath() {
    struct stat info;
    if(stat(_home.c_str(), &info) != 0 )
    {
        printf( "cannot access %s\n", CONFIG_FILE);
        return false;
    }
    return true;
}

void Config::getConfiguration()
{
    std::ifstream    file;
    nlohmann::json j;

    std::string line;
    file.open(_home + "/config");
    if (file.is_open())
    {
        file >> j;
        token = j.at("token").get<std::string>();
        host = j.at("host").get<std::string>();
    }
    file.close();
}

void Config::loadConfiguration() 
{
    if (this->checkConfigurationPath())
        getConfiguration();
    else
        this->createConfigurationFile();

}