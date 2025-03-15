#include "ToneSelectors.hpp"

ToneSelectors::ToneSelectors() { }

ToneSelectors::ToneSelectors(cmt::ResourceManager* resources) {
    m_resources = resources;
} 

void ToneSelectors::calculate(sf::Vector2f workspaceSize,
    float verticalBreak, float firstOffset) {

    m_cachedVOccurencies = static_cast<uint32_t>(
        (workspaceSize.x - firstOffset) / verticalBreak);
    m_cachedVertBreak = verticalBreak;

    setPos(sf::Vector2f{});
}

void ToneSelectors::setPos(sf::Vector2f pos) {
    calculateSelectorsPos(pos);
}

void ToneSelectors::move(sf::Vector2f amount) {
    calculateSelectorsPos(getPos() + amount);
}

sf::Vector2f ToneSelectors::getPos() {
    return m_selectors.front().getPosition();
}

void ToneSelectors::render(sf::RenderWindow& target) {
    for(int i{}; i < m_selectors.size(); ++i) {
        target.draw(m_selectors[i]);
    }
}

void ToneSelectors::calculateSelectorsPos(sf::Vector2f pos) {
    m_selectors.clear();
    for(uint16_t i{}; i < m_cachedVOccurencies; ++i) {
        sf::RectangleShape selector{};
        selector.setSize(sf::Vector2f{34, 34});
        selector.setTexture(&m_resources->getTexture(0));
        m_selectors.push_back(selector);

        float vOffset{m_cachedVertBreak * i};
        m_selectors.at(i).setPosition(sf::Vector2f(pos.x + vOffset, pos.y));
    }
}
