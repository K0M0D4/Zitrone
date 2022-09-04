#pragma once

#include "Button.hpp"

#include <SFML/Graphics.hpp>

namespace cmt {
    class ImageButton : public Button {
    public:
        ImageButton();
        ImageButton(const sf::Texture& texture,
            sf::Vector2f size, uint32_t padding = 0,
            sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
            sf::Color normal = sf::Color::White,
            sf::Color point = sf::Color(255, 255, 255, 140),
            sf::Color press = sf::Color::Transparent);

        void setPos(sf::Vector2f pos);

        void render(sf::RenderWindow& target);

    private:
        uint32_t m_padding;

    };
}