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

sf::Vector2f Config::getPageSize() {
    return sf::Vector2f{m_config.at("pageWidth"), m_config.at("pageHeight")};
}

sf::Vector2f Config::getCutLine() {
    return sf::Vector2f{m_config.at("cutLineX"), m_config.at("cutLineY")};
}

float Config::getFirstNoteOffset() {
    return m_config.at("firstNoteOffset");
}

sf::Vector2f Config::getBreaks() {
    return sf::Vector2f{m_config.at("verticalBreak"), m_config.at("horizontalBreak")};
}
