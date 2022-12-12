#include "Grid.hpp"

namespace cmt {
    Grid::Grid() {

    }

    Grid::Grid(sf::Vector2f workspaceSize, float verticalBreak,
        float horizontalBreak, float firstOffset) {

        uint32_t vLineOccurencies{static_cast<uint32_t>(
            (workspaceSize.x - firstOffset)
            / verticalBreak)};

        uint32_t hLineOccurencies{static_cast<uint32_t>(
            workspaceSize.y / horizontalBreak)};

        for(int32_t i{0}; i < vLineOccurencies; ++i) {
            float vOffset{firstOffset + verticalBreak * i};
            m_grid.emplace_back(DashLine{sf::Vector2f{vOffset, 0.0f},
                sf::Vector2f{vOffset, workspaceSize.y}, 20.0f,
                sf::Color(150.0f, 150.0f, 255.0f)});
        }

        for(int32_t i{1}; i < hLineOccurencies; ++i) {
            float hOffset{horizontalBreak * i};
            m_grid.emplace_back(DashLine{sf::Vector2f{0.0f, hOffset},
                sf::Vector2f{workspaceSize.x, hOffset}, 20.0f,
                sf::Color(255.0f, 150.0f, 150.0f)});
        }
    }

    void Grid::render(sf::RenderWindow& target) {
        for(uint32_t i{0}; i < m_grid.size(); ++i) {
            m_grid.at(i).render(target);
        }
    }
}