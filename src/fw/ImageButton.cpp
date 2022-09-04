#include "ImageButton.hpp"

namespace cmt {
    ImageButton::ImageButton() {}

    ImageButton::ImageButton(const sf::Texture& texture,
        sf::Vector2f size, uint32_t padding, sf::Vector2f pos,
        sf::Color normal, sf::Color point, sf::Color press) 
        : Button(size, pos, normal, point, press), m_padding(padding) {

        m_image.setSize(sf::Vector2f(size.x - m_padding * 2,
            size.y - m_padding * 2));
        m_image.setTexture(&texture);

        setPos(pos);
    }

    void ImageButton::setPos(sf::Vector2f pos) {
        Button::setPos(pos);
        m_image.setPosition(sf::Vector2f(
            m_rect.getPosition().x + m_padding,
            m_rect.getPosition().y + m_padding));
    }

    void ImageButton::render(sf::RenderWindow& target) {
        Button::render(target);
        target.draw(m_image);
    }
}