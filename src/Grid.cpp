#include "Grid.hpp"

Grid::Grid() {}

Grid::Grid(sf::Vector2f workspaceSize, float verticalBreak,
    float horizontalBreak, float firstOffset, cmt::ResourceManager* resources) {

    m_resources = resources;

    uint32_t vLineOccurencies{static_cast<uint32_t>(
        (workspaceSize.x - firstOffset)
        / verticalBreak)};

    uint32_t hLineOccurencies{static_cast<uint32_t>(
        workspaceSize.y / horizontalBreak)};

    for(int32_t i{0}; i < vLineOccurencies; ++i) {
        float vOffset{firstOffset + verticalBreak * i};
        m_vertLines.emplace_back(cmt::DashLine{sf::Vector2f{vOffset, 0.0f},
            sf::Vector2f{vOffset, workspaceSize.y}, 20.0f});
    }

    for(int32_t i{1}; i < hLineOccurencies; ++i) {
        float hOffset{horizontalBreak * i};
        m_horLines.emplace_back(cmt::DashLine{sf::Vector2f{0.0f, hOffset},
            sf::Vector2f{workspaceSize.x, hOffset}, 20.0f});
    }
}

bool Grid::setActiveLines(sf::Vector2i lines) {
    if(lines.x < m_vertLines.size() && lines.y < m_horLines.size()) {
        m_activeLines = lines;
        return true;
    }
    return false;
}

bool Grid::moveActiveLines(sf::Vector2i lines) {
    return setActiveLines(sf::Vector2i(m_activeLines.x + lines.x,
        m_activeLines.y + lines.y));
}

sf::Vector2i Grid::getActiveLines() {
    return m_activeLines;
}

void Grid::render(sf::RenderWindow& target) {
    for(uint32_t i{0}; i < m_vertLines.size(); ++i) {
        m_vertLines.at(i).setColor(m_resources->getTheme(0).getColor(3));
        m_vertLines.at(i).render(target);
    }
    for(uint32_t i{0}; i < m_horLines.size(); ++i) {
        m_horLines.at(i).setColor(m_resources->getTheme(0).getColor(3));
        m_horLines.at(i).render(target);
    }
    m_vertLines.at(m_activeLines.x).setColor(m_resources->getTheme(0).getColor(5));
    m_horLines.at(m_activeLines.y).setColor(m_resources->getTheme(0).getColor(5));
    m_vertLines.at(m_activeLines.x).render(target);
    m_horLines.at(m_activeLines.y).render(target);
}
