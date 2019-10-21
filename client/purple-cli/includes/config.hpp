#include <string>

class Config {
    private:
        std::string token;
        std::string _home;

        void        checkConfigurationPath();
        void        createConfigurationFile();
    public:
        void        loadConfiguration();
        Config();
};