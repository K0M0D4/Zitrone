#pragma once

#include <SFML/Graphics.hpp>

namespace cmt {
    class Note {
    public:
        Note(sf::Vector2f pos, sf::Vector2i coords);

        void setPos(sf::Vector2f pos, sf::Vector2i coords);

        sf::Vector2i getCoords();

        void render(sf::RenderWindow& target);

    private:
        sf::CircleShape m_circle{15.0f};

        sf::Vector2i m_coords{};

        //for later
        uint16_t m_chord{};

    };
}