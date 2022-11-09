#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

namespace cmt {
    class DashLine {
    public:
        DashLine();
        DashLine(sf::Vector2f start, sf::Vector2f end, float dashLength,
            sf::Color color = sf::Color::White);

        void setColor(sf::Color color);

        sf::Color getColor();

        void render(sf::RenderWindow& target);

    private:
        sf::VertexArray m_verts{};

        sf::Color m_color{};
    };
}