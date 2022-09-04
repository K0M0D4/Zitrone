#pragma once

#include "Button.hpp"

#include <SFML/Graphics.hpp>

namespace cmt {
    class TextButton : public Button {
    public:
        TextButton();
        TextButton(const sf::Font& font, const std::string& string,
            uint32_t verticalSize,
            sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
            uint32_t padding = 4,
            sf::Color textColor = sf::Color::Black,
            sf::Color normal = sf::Color::White,
            sf::Color point = sf::Color(255, 255, 255, 140),
            sf::Color press = sf::Color::Transparent);

        void setPos(sf::Vector2f pos);
        void setSize(sf::Vector2f size);
        void setSize(uint32_t verticalSize);
        void setFont(const sf::Font& font);
        void setString(const std::string& string);
        void setPadding(uint32_t padding);
        void setTextColor(sf::Color color);

        std::string getString();
        const uint32_t& getPadding();
        const sf::Color& getTextColor();

        void render(sf::RenderWindow& target);

    private:
        sf::Text m_text{};

        uint32_t m_padding{};

    };
}