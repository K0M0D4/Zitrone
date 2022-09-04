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
        void setSize(sf::Vector2f size);
        void setPadding(uint32_t padding);
        void setTexture(const sf::Texture& texture);

        const uint32_t& getPadding();

        void render(sf::RenderWindow& target);

    private:
        sf::RectangleShape m_image{};

        uint32_t m_padding{};

    };
}