#include "Button.hpp"

namespace cmt {
    Button::Button() {}

    Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color normal,
        sf::Color point, sf::Color press) {

        m_rect.setSize(size);
        m_rect.setPosition(pos);

        m_colors[0] = normal;
        m_colors[1] = point;
        m_colors[2] = press;
    }

    bool Button::isPressed(sf::Vector2f mousePos) {
        return (m_enable && isPointed(mousePos)
            && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            ? true: false;
    }

    bool Button::isPointed(sf::Vector2f mousePos) {
        return (m_rect.getGlobalBounds().contains(mousePos))
            ? true: false;
    }

    void Button::setPos(sf::Vector2f pos) {
        m_rect.setPosition(pos);
    }

    const sf::Vector2f& Button::getPos() {
        return m_rect.getPosition();
    }

    sf::FloatRect Button::getBounds() {
        return m_rect.getLocalBounds();
    }

    void Button::render(sf::RenderWindow& target) {
        processColors(target);
        target.draw(m_rect);
    }

    void Button::processColors(sf::RenderWindow& target) {
        sf::Vector2f mousePos{};
        mousePos.x = sf::Mouse::getPosition(target).x;
        mousePos.y = sf::Mouse::getPosition(target).y;

        if(isPressed(mousePos)) {
            m_rect.setFillColor(m_colors[2]);
        } else if(isPointed(mousePos)) {
            m_rect.setFillColor(m_colors[1]);
        } else {
            m_rect.setFillColor(m_colors[0]);
        }
    }
}   