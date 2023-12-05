#include "ProfileManager.hpp"

#include <fstream>



#include <iostream>



ProfileManager::ProfileManager() {

}

void ProfileManager::load() {
    std::ifstream profilesList{"res/profiles/list.app.json"};
    if(!profilesList.good())
        throw std::runtime_error("Error: Can't load profiles list file\n");

    json list{json::parse(profilesList)};

    std::cout << list << '\n';
    std::cout << list[0]["profiles"][0] << '\n';

    // for(const auto& profile : list.array()["profiles"]) {
    //     std::cout << profile << '\n';
    // }
}

// sf::Vector2f ProfileManager::getPageSize() {
//     return sf::Vector2f{m_config.at("pageWidth"), m_config.at("pageHeight")};
// }

// sf::Vector2f ProfileManager::getCutLine() {
//     return sf::Vector2f{m_config.at("cutLineX"), m_config.at("cutLineY")};
// }

// float ProfileManager::getFirstNoteOffset() {
//     return m_config.at("firstNoteOffset");
// }

// sf::Vector2f ProfileManager::getBreaks() {
//     return sf::Vector2f{m_config.at("verticalBreak"), m_config.at("horizontalBreak")};
// }
