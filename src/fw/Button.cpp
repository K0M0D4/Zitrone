#include "Button.hpp"

namespace cmt {
    Button::Button(const std::string& string, sf::Font& font,
            uint32_t textSize, sf::Vector2f size,
            sf::Vector2f pos, sf::Color text,
            sf::Color normal, sf::Color touch, sf::Color click) {

        create(string, font, textSize, size, pos, text, normal, touch, click);
    }

    Button::Button() {}

    void Button::create(const std::string& string, sf::Font& font,
            uint32_t textSize, sf::Vector2f size,
            sf::Vector2f pos, sf::Color text,
            sf::Color normal, sf::Color touch, sf::Color click) {

        m_text.setString(string);
        m_text.setFont(font);

        m_text.setCharacterSize(textSize);
        m_rect.setSize(size);
        m_rect.setPosition(pos);

        m_text.setFillColor(text);
        m_colors[0] = normal;
        m_colors[1] = touch;
        m_colors[2] = click;
    }

    bool Button::isClicked() {

    }

    void Button::enable(bool value) {
        m_enable = value;
    }

    bool Button::isEnabled() {
        return m_enable;
    }

    void Button::render(sf::RenderWindow& target) {
        // check if touched/clicked or no and change colors

        target.draw(m_rect);
        target.draw(m_text);
    }
}