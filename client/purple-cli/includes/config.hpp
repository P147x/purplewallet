#include <string>

class Config {
    private:
        std::string token;
        
        void createConfigurationFile();
    public:
        void loadConfiguration();
};