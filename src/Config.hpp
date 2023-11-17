#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

class Config {
public:
    Config();

    void load();

    std::string getLang();
    std::string getTheme();
    sf::Vector2f getPageSize();
    sf::Vector2f getCutLine();
    float getFirstNoteOffset();
    sf::Vector2f getBreaks();

private:
    json m_config{};

};
