#include "config.hpp"
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>

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
    std::ofstream file;

    file.open(_home + "/config", std::ofstream::out | std::ofstream::trunc);
    file << "";
    file.close();
}

void    Config::save()
{
    std::ofstream file;

    file.open(_home + "/config", std::ofstream::out | std::ofstream::trunc);
    file << token;
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
    //char            line[100];
    std::string line;
    file.open(_home + "/config");
    if (file.is_open())
    {
        file >> line;
        token = line;
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