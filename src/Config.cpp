#include "Config.hpp"

#include <fstream>

Config::Config() {
    load();
}

void Config::load() {
    std::ifstream config{"config.json"};
    if(!config.good())
        throw std::runtime_error("Error: Can't load config file\n");
    m_config = json::parse(config);
}

std::string Config::getLang() {
    return m_config.at("language");
}

std::string Config::getTheme() {
    return m_config.at("theme");
}
