#pragma once

#include <SFML/Graphics.hpp>

#include <array>

namespace cmt {
    class Button {
    public:
        Button();
        Button(sf::Vector2f size,
            sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
            sf::Color normal = sf::Color(100, 100, 100),
            sf::Color point = sf::Color(45, 45, 45),
            sf::Color press = sf::Color::Black);

        bool isPressed(sf::Vector2f mousePos);

        bool m_enable{true};

        void setPos(sf::Vector2f pos);

        void render(sf::RenderWindow& target);

    private:
        sf::RectangleShape m_rect{};

        std::array<sf::Color, 3> m_colors{};

        bool isPointed(sf::Vector2f mousePos);

    };
}