#pragma once

#include <array>

#include <SFML/Graphics.hpp>

namespace cmt {
    class Button {
    public:
        Button(const std::string& string, sf::Font& font,
            uint32_t textSize, sf::Vector2f size,
            sf::Vector2f pos, sf::Color text,
            sf::Color normal, sf::Color touch, sf::Color click);
        Button();

        void create(const std::string& string, sf::Font& font,
            uint32_t textSize, sf::Vector2f size,
            sf::Vector2f pos, sf::Color text,
            sf::Color normal, sf::Color touch, sf::Color click);

        bool isClicked(sf::Vector2f mousePos);

        void enable(bool value);
        bool isEnabled();

        void setPos(sf::Vector2f pos);

        void render(sf::RenderWindow& target);

    private:
        bool m_enable{true};
        sf::Text m_text;

        sf::RectangleShape m_rect;

        std::array<sf::Color, 3> m_colors;

        bool isTouched(sf::Vector2f mousePos);

        void setCenterText();

    };
}