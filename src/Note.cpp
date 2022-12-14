#include "Note.hpp"

namespace cmt {
    Note::Note(sf::Vector2f pos, sf::Vector2i coords) {
        m_circle.setOrigin(m_circle.getRadius(),
            m_circle.getRadius());
        setPos(pos, coords);
    }

    void Note::setPos(sf::Vector2f pos, sf::Vector2i coords) {
        m_circle.setPosition(pos);
        m_coords = coords;
    }

    sf::Vector2i Note::getCoords() {
        return m_coords;
    }

    void Note::render(sf::RenderWindow& target) {
        target.draw(m_circle);
    }
}