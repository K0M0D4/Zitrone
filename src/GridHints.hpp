#pragma once

#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace cmt {
    class GridHints {
    public:
        GridHints();
        GridHints(ResourceManager* resources);

        // after loading a font file;
        void calculate(sf::Vector2f workspaceSize,
            float verticalBreak, float firstOffset);

        void setPos(sf::Vector2f pos);
        void move(sf::Vector2f amount);

        sf::Vector2f getPos();

        void render(sf::RenderWindow& target);

    private:
        ResourceManager* m_resources{};

        std::vector<std::string> m_hintData{"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
            "A", "A#", "B"};
        std::vector<sf::Text> m_notes{};

        uint32_t m_cachedVOccurencies{};
        float m_cachedVertBreak{};

        void calculateHintsData();
        void calculateHintsPos(sf::Vector2f pos);
    };
}