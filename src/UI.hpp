#pragma once

#include "fw/Button.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Window.hpp>

#include <array>

namespace cmt {
    class UI {
    public:
        UI();
        UI(ResourceManager& resources, const std::string& langFilepath);

        void render(sf::RenderWindow& target);

        void recalculate(sf::RenderWindow& window);

        // horizontal navbar
        TextButton m_saveBtn{};
        TextButton m_saveAsBtn{};
        TextButton m_exportBtn{};
        TextButton m_openBtn{};
        TextButton m_settingsBtn{};

        // vertical navbar
        ImageButton m_addNoteBtn{};
        ImageButton m_deleteBtn{};
        std::array<TextButton, 7> m_chBtn{};

    private:
        void initNavBars(ResourceManager& resources);

        uint16_t m_padding{4};
        sf::Color m_btnTextColor{};
        sf::Color m_btnNormalColor{};
        sf::Color m_btnPointColor{};
        sf::Color m_btnPressColor{};

        std::array<std::string, 5> m_textData{};

        ImageButton createImageBtn(ResourceManager& resources, uint16_t textureID);
        TextButton createTextBtn(ResourceManager& resources, const std::string& text,
            sf::Vector2f pos);

        void loadLanguage(const std::string& filepath);

    };
}