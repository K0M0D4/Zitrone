#pragma once

#include <SFML/Graphics.hpp>

namespace cmt {
    class Note {
    public:
        Note();
        Note(sf::Vector2f pos);

        void setPos(sf::Vector2f pos);

        void render(sf::RenderWindow& target);

    private:
        sf::CircleShape m_circle{15.0f};

        //for later
        uint16_t m_chord{};

    };
}