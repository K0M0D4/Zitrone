#pragma once

#include "fw/Buttons.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Window.hpp>

#include <array>

class UI {
public:
    UI();
    UI(cmt::ResourceManager& resources, const std::string& langFilepath);

    void render(sf::RenderWindow& target);

    void recalculate(sf::RenderWindow& window);

    // horizontal navbar
    cmt::TextButton m_saveBtn{};
    cmt::TextButton m_saveAsBtn{};
    cmt::TextButton m_exportBtn{};
    cmt::TextButton m_openBtn{};
    cmt::TextButton m_settingsBtn{};

    // vertical navbar
    cmt::ImageButton m_addNoteBtn{};
    cmt::ImageButton m_deleteBtn{};
    std::array<cmt::TextButton, 7> m_chBtn{};

private:
    void initNavBars(cmt::ResourceManager& resources);

    uint16_t m_padding{4};
    sf::Color m_btnTextColor{};
    sf::Color m_btnNormalColor{};
    sf::Color m_btnPointColor{};
    sf::Color m_btnPressColor{};

    std::array<std::string, 5> m_textData{};

    cmt::ImageButton createImageBtn(cmt::ResourceManager& resources, uint16_t textureID);
    cmt::TextButton createTextBtn(cmt::ResourceManager& resources, const std::string& text,
        sf::Vector2f pos);

    void loadLanguage(const std::string& filepath);

};
