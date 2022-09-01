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

        setCenterText();

        m_text.setFillColor(text);
        m_colors[0] = normal;
        m_colors[1] = touch;
        m_colors[2] = click;
    }

    bool Button::isClicked(sf::Vector2f mousePos) {
        if(m_enable && isTouched(mousePos)
            && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            
            return true;

        return false;
    }

    bool Button::isTouched(sf::Vector2f mousePos) {
        if(m_rect.getGlobalBounds().contains(mousePos)) return true;

        return false;
    }

    void Button::enable(bool value) {
        m_enable = value;
    }

    bool Button::isEnabled() {
        return m_enable;
    }

    void Button::setPos(sf::Vector2f pos) {
        m_rect.setPosition(pos);
        setCenterText();
    }

    void Button::render(sf::RenderWindow& target) {
        sf::Vector2f mousePos{};
        mousePos.x = sf::Mouse::getPosition(target).x;
        mousePos.y = sf::Mouse::getPosition(target).y;

        if(isClicked(mousePos)) {
            m_rect.setFillColor(m_colors[2]);
        } else if(isTouched(mousePos)) {
            m_rect.setFillColor(m_colors[1]);
        } else {
            m_rect.setFillColor(m_colors[0]);
        }

        target.draw(m_rect);
        target.draw(m_text);
    }

    void Button::setCenterText() {
        m_text.setPosition(sf::Vector2f(
            m_rect.getPosition().x + (m_rect.getLocalBounds().width
                - m_text.getLocalBounds().width) / 2,
            m_rect.getPosition().y + (m_rect.getLocalBounds().height
                - m_text.getLocalBounds().height) / 2));
    }
}