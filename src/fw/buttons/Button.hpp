#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <vector>

namespace cmt {
    class Button {
    public:
        Button();
        Button(sf::Vector2f size,
            sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
            sf::Color normal = sf::Color::White,
            sf::Color point = sf::Color(255, 255, 255, 140),
            sf::Color press = sf::Color::Transparent);

        bool isPointed(sf::Vector2f mousePos);

        bool enable{true};

        void setPos(sf::Vector2f pos);
        void setSize(sf::Vector2f size);
        void setColors(sf::Color normal, sf::Color point, sf::Color press);

        const sf::Vector2f& getPos();
        const sf::Vector2f& getSize();
        std::array<sf::Color, 3>& getColors();
        sf::FloatRect getBounds();

        void render(sf::RenderWindow& target);

    protected:
        sf::RectangleShape m_rect{};

        std::array<sf::Color, 3> m_colors{};

        bool isPressed(sf::Vector2f mousePos);

        void processColors(sf::RenderWindow& target);
    };
}