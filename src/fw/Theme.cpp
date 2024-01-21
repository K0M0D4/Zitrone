#include "Theme.hpp"

#include <cstdio>

namespace cmt {
    Theme::Theme(const std::string& filepath) {
        load(filepath);
    }

    void Theme::load(const std::string& filepath) {
        std::ifstream theme{filepath};
        if(!theme.good())
            throw std::runtime_error("Error: Can't load theme file\n");
        m_theme = json::parse(theme);
    }

    sf::Color Theme::getBgColor() {
        return hexToSfColor(m_theme.at("backgroundColor"));
    }

    sf::Color Theme::getOutlineColor() {
        return hexToSfColor(m_theme.at("outlineColor"));
    }

    sf::Color Theme::getBreaksColor() {
        return hexToSfColor(m_theme.at("breaksColor"));
    }

    sf::Color Theme::getNotesColor() {
        return hexToSfColor(m_theme.at("notesColor"));
    }

    sf::Color Theme::getALColor() {
        return hexToSfColor(m_theme.at("activeLineColor"));
    }

    std::string Theme::getTGUIFilepath() {
        return m_theme.at("tguiFile");
    }

    std::string Theme::getAddNoteBtnImgFilepath() {
        return m_theme.at("addNoteBtnImg");
    }

    std::string Theme::getDeleteNoteBtnImgFilepath() {
        return m_theme.at("deleteNoteBtnImg");
    }

    std::string Theme::getChangeChordPosBtnImgFilepath() {
        return m_theme.at("changeChordPosBtnImg");
    }

    std::string Theme::getArrowUpImgFilepath() {
        return m_theme.at("arrowUpImg");
    }

    std::string Theme::getEditImgFilepath() {
        return m_theme.at("editImg");
    }

    std::string Theme::getSaveImgFilepath() {
        return m_theme.at("saveImg");
    }

    sf::Color Theme::hexToSfColor(const std::string& hexColor) {
        std::string colorStr{hexColor};

        colorStr.erase(0, 1);

        int r, g, b;
        sscanf(colorStr.c_str(), "%02x%02x%02x", &r, &g, &b);

        sf::Color color{static_cast<sf::Uint8>(r), 
            static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b)};

        return color;
    }
}