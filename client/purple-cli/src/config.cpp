#include "config.hpp"
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CONFIG_FILE "/.config/purplewallet"

Config::Config()
{
    _home = getenv("HOME");
    _home += CONFIG_FILE;
}

void Config::createConfigurationFile() 
{

    mkdir(_home.c_str(), 0777);
}

void Config::checkConfigurationPath() {
    struct stat info;
    if(stat(_home.c_str(), &info) != 0 )
        printf( "cannot access %s\n", CONFIG_FILE);
    std::cout << "ok";
}

void Config::loadConfiguration() 
{
    this->checkConfigurationPath();
}