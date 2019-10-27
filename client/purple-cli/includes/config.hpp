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
        void        loadConfiguration();
        std::string getToken();
        void        setToken(std::string);

        Config();

    void        save();

    void removeConfiguration();
};