#include "ResourceManager.hpp"

namespace cmt {
    int32_t ResourceManager::loadTexture(const std::string& filepath) {
        sf::Texture texture;
        if(!texture.loadFromFile(filepath))
            throw std::runtime_error("Can't load texture: " + filepath);
        
        m_textures.push_back(texture);
        return m_textures.size() - 1;
    }

    int32_t ResourceManager::loadFont(const std::string& filepath) {
        sf::Font font;
        if(!font.loadFromFile(filepath))
            throw std::runtime_error("Can't load font: " + filepath);
        
        m_fonts.push_back(font);
        return m_fonts.size() - 1;
    }

    sf::Texture& ResourceManager::getTexture(uint32_t ID) {
        if(m_textures.size() <= ID)
            throw std::runtime_error(
                "Resource manager can't return texture with ID: "
                + std::to_string(ID));
        
        return m_textures.at(ID);
    }

    sf::Font& ResourceManager::getFont(uint32_t ID) {
        if(m_fonts.size() <= ID)
            throw std::runtime_error(
                "Resource manager can't return font with ID: "
                + std::to_string(ID));

        return m_fonts.at(ID);
    }
}