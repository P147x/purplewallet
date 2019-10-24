#include <string>

class Config {
    private:
        std::string token;
        std::string _home;

        bool        checkConfigurationPath();
        void        createConfigurationFile();
        void        getConfiguration();
        void        save();
    public:
        void        loadConfiguration();
        std::string getToken();
        void        setToken(std::string);

        Config();
};