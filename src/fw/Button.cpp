#include "Button.hpp"

#include <cstdio>
#include <cmath>

namespace cmt {
    Button::Button(const std::string& string, sf::Font& font,
            uint32_t textSize, sf::Vector2f size,
            sf::Vector2f pos, sf::Color text,
            sf::Color normal, sf::Color touch, sf::Color click) {

        if(textSize > size.y) {
            uint32_t newSize{static_cast<uint32_t>(round(size.y))};
            printf("Warning: button text size too big, changing to: %u\n",
                newSize);
            textSize = newSize;
        }

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

    Button::Button() {}

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

    void Button::enableTexture(const sf::Texture& texture) {
        m_rect.setTexture(&texture);

        if(sizeof(texture) > 40)
            m_text.setString("");
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
        sf::FloatRect textRect = m_text.getLocalBounds();
        m_text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);

        sf::Vector2f newPos{};
        newPos.x = m_rect.getPosition().x
            + m_rect.getLocalBounds().width / 2.0f;
        newPos.y = m_rect.getPosition().y
            + m_rect.getLocalBounds().height / 2.0f;

        m_text.setPosition(sf::Vector2f(round(newPos.x), round(newPos.y)));
    }
}