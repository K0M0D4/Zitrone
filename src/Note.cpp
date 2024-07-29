#include "Note.hpp"

Note::Note(sf::Vector2f pos, sf::Vector2i coords, sf::Font& font,
    sf::Color color, float chordSize) {

    m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());

    m_chordText.setFont(font);
    setChordSize(chordSize);
    setColor(color);
    setPos(pos, coords);
}

void Note::setPos(sf::Vector2f pos, sf::Vector2i coords) {
    m_circle.setPosition(pos);
    repositionChord();
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
        float chordTextWidth{m_chordText.getGlobalBounds().width};
        float chordTextHeight{m_chordText.getGlobalBounds().height};
        m_chordText.setOrigin(chordTextWidth / 2, chordTextHeight / 2);

        repositionChord();
    }
}

void Note::setChordPos(int position) {
    if(position > 0 && position <= 9) {
        if(position != 5) {
            m_chordPos = position;
            repositionChord();
        }
    }
}

void Note::setColor(sf::Color color) {
    m_circle.setFillColor(color);
    m_chordText.setFillColor(color);
}

void Note::setChordSize(float chordSize) {
    m_chordText.setCharacterSize(chordSize);
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

int Note::getChordPosition() {
    return m_chordPos;
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

void Note::repositionChord() {
    float newX{};
    float newY{};

    // number in case means button on numpad

    switch(m_chordPos) {
    case 7:
        newX = m_pos.x - m_circle.getRadius() * 2;
        newY = m_pos.y - m_circle.getRadius() * 4;
        break;
    case 8:
        newX = m_pos.x;
        newY = m_pos.y - m_circle.getRadius() * 5;
        break;
    case 9:
        newX = m_pos.x + m_circle.getRadius() * 2;
        newY = m_pos.y - m_circle.getRadius() * 4;
        break;
    case 6:
        newX = m_pos.x + m_circle.getRadius() * 3;
        newY = m_pos.y - m_circle.getRadius();
        break;
    case 3:
        newX = m_pos.x + m_circle.getRadius() * 2;
        newY = m_pos.y + m_circle.getRadius();
        break;
    case 2:
        newX = m_pos.x;
        newY = m_pos.y + m_circle.getRadius() * 2;
        break;
    case 1:
        newX = m_pos.x - m_circle.getRadius() * 2;
        newY = m_pos.y + m_circle.getRadius();
        break;
    case 4:
        newX = m_pos.x - m_circle.getRadius() * 3;
        newY = m_pos.y - m_circle.getRadius();
        break;
    }

    m_chordText.setPosition(sf::Vector2f{newX, newY});
}
