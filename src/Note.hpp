#pragma once

#include <SFML/Graphics.hpp>

namespace cmt {
    class Note {
    public:
        Note(sf::Vector2f pos, sf::Vector2i coords, sf::Font& font, sf::Color color);

        void setPos(sf::Vector2f pos, sf::Vector2i coords);
        void setChord(uint16_t chord);

        sf::Vector2i getCoords();
        sf::Vector2f getPos();

        void render(sf::RenderWindow& target);

    private:

        sf::CircleShape m_circle{15.0f};
        sf::Text m_chordText{};

        sf::Vector2i m_coords{};
        sf::Vector2f m_pos{};

        uint16_t m_chord{};

    };
}