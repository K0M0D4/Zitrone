#pragma once

#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class ToneSelectors {
public:
    ToneSelectors();
    ToneSelectors(cmt::ResourceManager* resources);

    // after loading a font file;
    void calculate(sf::Vector2f workspaceSize,
        float verticalBreak, float firstOffset);

    void setPos(sf::Vector2f pos);
    void move(sf::Vector2f amount);

    sf::Vector2f getPos();

    void render(sf::RenderWindow& target);

private:
    cmt::ResourceManager* m_resources{};

    std::vector<sf::RectangleShape> m_selectors{};
    std::vector<double> m_values{};

    uint32_t m_cachedVOccurencies{};
    float m_cachedVertBreak{};

    void calculateSelectorsPos(sf::Vector2f pos);
};
