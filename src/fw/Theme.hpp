#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <fstream>

namespace cmt {
    class Theme {
    public:
        Theme(const std::string& filepath);

        void load(const std::string& filepath);

        sf::Color getColor(uint16_t which);

    private:
        static const uint16_t m_colorsCount{8};
        std::array<sf::Color, m_colorsCount> m_colors{};
    };
}