#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

namespace cmt {
    class ResourceManager {
    public:
        int32_t loadTexture(const std::string& filepath);
        int32_t loadFont(const std::string& filepath);

        sf::Texture& getTexture(uint32_t ID);
        sf::Font& getFont(uint32_t ID);

    private:
        std::vector<sf::Texture> m_textures;
        std::vector<sf::Font> m_fonts;

    };
}