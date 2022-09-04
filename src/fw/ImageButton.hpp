#pragma once

#include "Button.hpp"

#include <SFML/Graphics.hpp>

// padding for image

namespace cmt {
    class ImageButton : public Button {
    public:
        ImageButton();
        ImageButton(const sf::Texture& texture, sf::Vector2f size,
            sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));

    };
}