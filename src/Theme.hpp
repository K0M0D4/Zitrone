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
        std::array<sf::Color, 5> m_colors{};
    };
}