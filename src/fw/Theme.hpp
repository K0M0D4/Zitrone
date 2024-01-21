#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <fstream>

using json = nlohmann::json;

namespace cmt {
    class Theme {
    public:
        Theme(const std::string& filepath);

        void load(const std::string& filepath);

        sf::Color getBgColor();
        sf::Color getOutlineColor();
        sf::Color getBreaksColor();
        sf::Color getNotesColor();
        sf::Color getALColor();

        std::string getTGUIFilepath();

        std::string getAddNoteBtnImgFilepath();
        std::string getDeleteNoteBtnImgFilepath();
        std::string getChangeChordPosBtnImgFilepath();
        std::string getArrowUpImgFilepath();
        std::string getEditImgFilepath();
        std::string getSaveImgFilepath();

    private:
        static const uint16_t m_colorsCount{8};
        std::array<sf::Color, m_colorsCount> m_colors{};

        json m_theme{};

        sf::Color hexToSfColor(const std::string& hexColor);

    };
}