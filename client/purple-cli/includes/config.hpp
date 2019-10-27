#include <string>

class Config {
    private:
        std::string token;
        std::string host;
        std::string _home;

        bool        checkConfigurationPath();
        void        createConfigurationFile();
        void        getConfiguration();

public:
        bool        checkConfiguration();
        void        loadConfiguration();
        std::string getToken();
        void        setToken(std::string);
        void        setHostname(std::string);
        std::string getHostname();

        Config();

    void        save();

    void removeConfiguration();
};