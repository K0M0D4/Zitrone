#include "ImageButton.hpp"

namespace cmt {
    ImageButton::ImageButton() {}

    ImageButton::ImageButton(const sf::Texture& texture, sf::Vector2f size,
        sf::Vector2f pos) 
        : Button(size, pos) {

        m_colors[0] = sf::Color::White;
        m_colors[1] = sf::Color(255, 255, 255, 140);
        m_colors[2] = sf::Color::Transparent;

        m_rect.setTexture(&texture);
    }

}