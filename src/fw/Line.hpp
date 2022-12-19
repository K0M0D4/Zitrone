#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

namespace cmt {
    class Line {
    public:
        Line();
        Line(sf::Vector2f start, sf::Vector2f end,
            sf::Color color = sf::Color::White);

        void setColor(sf::Color color);

        sf::Color getColor();

        void render(sf::RenderWindow& target);

    private:
        sf::VertexArray m_verts{sf::Lines, 0};

        sf::Color m_color{};
    };
}