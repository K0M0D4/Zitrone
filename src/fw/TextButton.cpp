#include "TextButton.hpp"

namespace cmt {
    TextButton::TextButton() {}

    TextButton::TextButton(const sf::Font& font, const std::string& string,
        uint32_t verticalSize, sf::Vector2f pos,
        uint32_t padding, sf::Color textColor,
        sf::Color normal, sf::Color point, sf::Color press) 
        : Button(sf::Vector2f(0.0f, verticalSize), pos,
            normal, point, press), m_padding(padding) {

        setFont(font);
        setTextColor(textColor);
        setString(string);
        setSize(verticalSize);
        setPos(pos);
    }

    // setters
    void TextButton::setPos(sf::Vector2f pos) {
        Button::setPos(pos);

        sf::FloatRect textRect = m_text.getLocalBounds();

        sf::Vector2f newPos{};
        newPos.x = m_rect.getPosition().x
            + m_rect.getLocalBounds().width / 2.0f
            - textRect.left - textRect.width / 2.0f;
        newPos.y = m_rect.getPosition().y
            + m_rect.getLocalBounds().height / 2.0f
            - textRect.top - textRect.height / 2.0f;

        m_text.setPosition(sf::Vector2f(
            static_cast<int32_t>(newPos.x),
            static_cast<int32_t>((newPos.y))));
    }

    void TextButton::setSize(sf::Vector2f size) {
        setSize(size.y);
    }

    void TextButton::setSize(uint32_t verticalSize) {
        m_text.setCharacterSize(static_cast<uint32_t>(verticalSize
            - m_padding * 2));
        m_rect.setSize(sf::Vector2f(m_text.getLocalBounds().width
            + m_padding * 2,
            m_rect.getSize().y));
    }

    void TextButton::setFont(const sf::Font& font) {
        m_text.setFont(font);
    }

    void TextButton::setString(const std::string& string) {
        m_text.setString(string);
    }

    void TextButton::setPadding(uint32_t padding) {
        m_padding = padding;
    }

    void TextButton::setTextColor(sf::Color color) {
        m_text.setFillColor(color);
    }

    // getters
    std::string TextButton::getString() {
        return m_text.getString();
    }

    const uint32_t& TextButton::getPadding() {
        return m_padding;
    }

    const sf::Color& TextButton::getTextColor() {
        return m_text.getFillColor();
    }


    void TextButton::render(sf::RenderWindow& target) {
        Button::render(target);
        target.draw(m_text);
    }
}