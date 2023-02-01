#include "Note.hpp"

namespace cmt {
    Note::Note(sf::Vector2f pos, sf::Vector2i coords, sf::Font& font, sf::Color color) {
        m_circle.setOrigin(m_circle.getRadius(),
            m_circle.getRadius());

        m_chordText.setFont(font);
        m_chordText.setCharacterSize(30);
        setColor(color);
        setPos(pos, coords);
    }

    void Note::setPos(sf::Vector2f pos, sf::Vector2i coords) {
        m_circle.setPosition(pos);
        m_chordText.setPosition(sf::Vector2f{pos.x + 5, pos.y});
        m_pos = pos;
        m_coords = coords;
    }

    void Note::setChord(uint16_t chord) {
        if(chord >= 0 && chord <= 6) {
            m_chord = chord;
        } else {
            m_chord = 0;
        }
        if(m_chord == 0) {
            m_chordText.setString("");
        } else {
            m_chordText.setString(std::to_string(m_chord));
        }
    }

    void Note::setColor(sf::Color color) {
        m_circle.setFillColor(color);
        m_chordText.setFillColor(color);
    }

    sf::Vector2i Note::getCoords() {
        return m_coords;
    }

    sf::Vector2f Note::getPos() {
        return m_pos;
    }

    uint16_t Note::getChord() {
        return m_chord;
    }

    sf::Color Note::getColor() {
        return m_circle.getFillColor();
    }

    void Note::render(sf::RenderTarget& target) {
        target.draw(m_circle);
        if(m_chord >= 0 && m_chord <= 6) {
            target.draw(m_chordText);
        }
    }
}