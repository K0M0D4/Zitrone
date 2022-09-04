#include "ImageButton.hpp"

namespace cmt {
    ImageButton::ImageButton() {}

    ImageButton::ImageButton(const sf::Texture& texture, sf::Vector2f size,
        sf::Vector2f pos) {

        m_rect.setSize(size);
        m_rect.setPosition(pos);

        m_rect.setTexture(&texture);
    }

    void ImageButton::render(sf::RenderWindow& target) {
        // fix code repetition with inheritance
        sf::Vector2f mousePos{};
        mousePos.x = sf::Mouse::getPosition(target).x;
        mousePos.y = sf::Mouse::getPosition(target).y;

        if(isPressed(mousePos)) {
            m_rect.setFillColor(sf::Color::Transparent);
        } else if(isPointed(mousePos)) {
            m_rect.setFillColor(sf::Color(255, 255, 255, 140));
        } else {
            m_rect.setFillColor(sf::Color(255, 255, 255, 255));
        }

        target.draw(m_rect);
    }

}