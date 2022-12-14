#include "Note.hpp"

namespace cmt {
    Note::Note() {
        
    }

    Note::Note(sf::Vector2f pos) {
        setPos(pos);
    }

    void Note::setPos(sf::Vector2f pos) {
        m_circle.setPosition(pos);
    }

    void Note::render(sf::RenderWindow& target) {
        target.draw(m_circle);
    }
}