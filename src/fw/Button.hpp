#pragma once

#include <array>

#include <SFML/Graphics.hpp>

namespace cmt {
    class Button {
    public:
        Button(const std::string& string, sf::Font& font,
            uint32_t textSize = 25,
            sf::Vector2f size = sf::Vector2f(100.0f, 25.0f),
            sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
            sf::Color text = sf::Color::Black,
            sf::Color normal = sf::Color(100, 100, 100),
            sf::Color touch = sf::Color(45, 45, 45),
            sf::Color click = sf::Color::Black);
        Button();

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