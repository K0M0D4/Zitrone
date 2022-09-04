#include "ImageButton.hpp"

namespace cmt {
    ImageButton::ImageButton() {}

    ImageButton::ImageButton(const sf::Texture& texture,
        sf::Vector2f size, uint32_t padding, sf::Vector2f pos,
        sf::Color normal, sf::Color point, sf::Color press) 
        : Button(size, pos, normal, point, press), m_padding(padding) {

        sf::RectangleShape image{};

        image.setSize(sf::Vector2f(size.x - m_padding * 2,
            size.y - m_padding * 2));
        image.setTexture(&texture);

        m_drawables.push_back(image);

        setPos(pos);
    }

    void ImageButton::setPos(sf::Vector2f pos) {
        Button::setPos(pos);
        m_drawables.at(1).setPosition(sf::Vector2f(
            m_drawables.at(0).getPosition().x + m_padding,
            m_drawables.at(0).getPosition().y + m_padding));
    }

    void ImageButton::render(sf::RenderWindow& target) {
        Button::render(target);
    }
}