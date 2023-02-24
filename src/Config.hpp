#pragma once

#include <SFML/Graphics.hpp>

#include <array>

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
    std::string m_language{};
    std::string m_theme{};
    std::array<float, 7> m_numbers{};
};
