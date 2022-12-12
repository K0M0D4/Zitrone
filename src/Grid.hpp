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

        bool setActiveLines(sf::Vector2i lines);
        bool moveActiveLines(sf::Vector2i lines);

        sf::Vector2i getActiveLines();

        void render(sf::RenderWindow& target);

    private:
        std::vector<DashLine> m_vertLines{};
        std::vector<DashLine> m_horLines{};

        sf::Vector2i m_activeLines{};
    };
}