#include "GridHints.hpp"

namespace cmt {
    GridHints::GridHints() { }

    GridHints::GridHints(ResourceManager* resources) {
        m_resources = resources;
    } 

    void GridHints::calculate(sf::Vector2f workspaceSize,
        float verticalBreak, float firstOffset) {

        m_cachedVOccurencies = static_cast<uint32_t>(
            (workspaceSize.x - firstOffset) / verticalBreak);
        m_cachedVertBreak = verticalBreak;

        calculateHintsData();

        setPos(sf::Vector2f{});
    }

    void GridHints::setPos(sf::Vector2f pos) {
        calculateHintsPos(pos);
    }

    void GridHints::move(sf::Vector2f amount) {
        calculateHintsPos(getPos() + amount);
    }

    sf::Vector2f GridHints::getPos() {
        return m_notes.front().getPosition();
    }

    void GridHints::render(sf::RenderWindow& target) {
        for(auto& hint : m_notes) {
            target.draw(hint);
        }
    }

    void GridHints::calculateHintsData() {
        int16_t hintIterator{-1};
        for(uint16_t i{}; i < m_cachedVOccurencies; ++i) {
            ++hintIterator;
            if(hintIterator >= m_hintData.size()) {
                hintIterator = 0;
            }

            m_notes.emplace_back(sf::Text{m_hintData.at(hintIterator),
                m_resources->getFont(0), 20});
        }
    }

    void GridHints::calculateHintsPos(sf::Vector2f pos) {
        for(uint16_t i{}; i < m_cachedVOccurencies; ++i) {
            float vOffset{m_cachedVertBreak * i};
            m_notes.at(i).setPosition(sf::Vector2f(pos.x + vOffset,
                pos.y));
            
            m_notes.at(i).setFillColor(m_resources->getTheme(0).getColor(6));
        }
    }
}