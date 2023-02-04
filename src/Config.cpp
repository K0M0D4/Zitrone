#include "Config.hpp"

#include <fstream>

Config::Config() {
    std::ifstream config{"config"};
    if(!config.good())
        throw std::runtime_error("Error: Can't load config file\n");

    std::string buffer{};

    getline(config, buffer);
    m_language = buffer;
    getline(config, buffer);
    m_theme = buffer;

    // page size
    getline(config, buffer);
    m_numbers.at(0) = std::stof(buffer);
    getline(config, buffer);
    m_numbers.at(1) = std::stof(buffer);

    // cut line
    getline(config, buffer);
    m_numbers.at(2) = std::stof(buffer);
    getline(config, buffer);
    m_numbers.at(3) = std::stof(buffer);

    // first note offset, v-break and h-break
    getline(config, buffer);
    m_numbers.at(4) = std::stof(buffer);
    getline(config, buffer);
    m_numbers.at(5) = std::stof(buffer);
    getline(config, buffer);
    m_numbers.at(6) = std::stof(buffer);

    config.close();
}

std::string Config::getLang() {
    return m_language;
}

std::string Config::getTheme() {
    return m_theme;
}

sf::Vector2f Config::getPageSize() {
    return sf::Vector2f{m_numbers.at(0), m_numbers.at(1)};
}

sf::Vector2f Config::getCutLine() {
    return sf::Vector2f{m_numbers.at(2), m_numbers.at(3)};
}

float Config::getFirstNoteOffset() {
    return m_numbers.at(4);
}

sf::Vector2f Config::getBreaks() {
    return sf::Vector2f{m_numbers.at(5), m_numbers.at(6)};
}
