#include "config.hpp"
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define CONFIG_FILE "/.config/purplewallet" 

void Config::createConfigurationFile() 
{
    std::string home;
    home = getenv("HOME");
    home += CONFIG_FILE;
    mkdir(home.c_str(), 0777);

}

void Config::loadConfiguration() 
{
}