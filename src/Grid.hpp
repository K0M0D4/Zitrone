#pragma once

#include "fw/DashLine.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace cmt {
    class Grid {
    public:
        Grid();
        Grid(sf::Vector2f workspaceSize, float verticalBreak,
            float horizontalBreak, float firstOffset);

        void render(sf::RenderWindow& target);

    private:
        std::vector<DashLine> m_grid{};
    };
}