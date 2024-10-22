#pragma once

#include <SFML/Graphics.hpp>

class Note {
public:
    Note(sf::Vector2f pos, sf::Vector2i coords, sf::Font& font, sf::Color color, float chordSize);

    void setPos(sf::Vector2f pos, sf::Vector2i coords);
    void setChord(uint16_t chord);
    void setChordPos(int position);
    void setColor(sf::Color color);
    void setChordSize(float chordSize);

    sf::Vector2i getCoords();
    sf::Vector2f getPos();
    uint16_t getChord();
    int getChordPosition();
    sf::Color getColor();

    void repositionChord();

    void render(sf::RenderTarget& target);

private:

    sf::CircleShape m_circle{20.0f};
    sf::Text m_chordText{};

    sf::Vector2i m_coords{};
    sf::Vector2f m_pos{};

    uint16_t m_chord{};
    int m_chordPos{3};

};
