#pragma once

#include "fw/DashLine.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class Grid {
public:
    Grid();
    Grid(sf::Vector2f workspaceSize, float verticalBreak,
        float horizontalBreak, float firstOffset, cmt::ResourceManager* resources);

    bool setActiveLines(sf::Vector2i lines);
    bool moveActiveLines(sf::Vector2i lines);

    sf::Vector2i getActiveLines();

    void render(sf::RenderWindow& target);

private:
    cmt::ResourceManager* m_resources{};

    std::vector<cmt::DashLine> m_vertLines{};
    std::vector<cmt::DashLine> m_horLines{};

    sf::Vector2i m_activeLines{};
};
