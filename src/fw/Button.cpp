#include "Button.hpp"

namespace cmt {
    Button::Button() {}

    Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color normal,
        sf::Color point, sf::Color press) {

        sf::RectangleShape rect{};

        rect.setSize(size);
        rect.setPosition(pos);

        m_drawables.push_back(rect);

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
        return (m_drawables.at(0).getGlobalBounds().contains(mousePos))
            ? true: false;
    }

    void Button::setPos(sf::Vector2f pos) {
        m_drawables.at(0).setPosition(pos);
    }

    void Button::render(sf::RenderWindow& target) {
        processColors(target);
        for(auto& drawable : m_drawables) {
            target.draw(drawable);
        }
    }

    void Button::processColors(sf::RenderWindow& target) {
        sf::Vector2f mousePos{};
        mousePos.x = sf::Mouse::getPosition(target).x;
        mousePos.y = sf::Mouse::getPosition(target).y;

        for(auto& drawable : m_drawables) {
            if(isPressed(mousePos)) {
                drawable.setFillColor(m_colors[2]);
            } else if(isPointed(mousePos)) {
                drawable.setFillColor(m_colors[1]);
            } else {
                drawable.setFillColor(m_colors[0]);
            }
        }
    }
}   