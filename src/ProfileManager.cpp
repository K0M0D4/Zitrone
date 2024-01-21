#include "ProfileManager.hpp"

#include <fstream>

ProfileManager::ProfileManager() {

}

void ProfileManager::load() {
    std::ifstream profilesList{"res/profiles/list.app.json"};
    if(!profilesList.good())
        throw std::runtime_error("Error: Can't load profiles list file\n");

    json list{json::parse(profilesList)};

    m_profilesCount = list.at(0).at("profiles").size();
    
    for(int i{}; i < list.at(0).at("profiles").size(); ++i) {
        std::ifstream currentBuffer{"res/profiles/"
            + std::string{list[0]["profiles"][i]} + ".json"};
        m_profileNames[i] = std::string{list[0]["profiles"][i]};

        json profileBuf{json::parse(currentBuffer)};

        m_profiles[std::string{list[0]["profiles"][i]}] = profileBuf;
    }
}

void ProfileManager::switchProfile(const std::string& profile) {
    m_currentProfile = profile;
}

int ProfileManager::getProfilesCount() {
    return m_profilesCount;
}

std::string ProfileManager::getName(int id) {
    return m_profileNames.at(id);
}

sf::Vector2f ProfileManager::getPageSize() {
    return sf::Vector2f{m_profiles.at(m_currentProfile)[0]["pageWidth"], m_profiles.at(m_currentProfile)[0]["pageHeight"]};
}

sf::Vector2f ProfileManager::getCutLine() {
    return sf::Vector2f{m_profiles.at(m_currentProfile)[0]["cutLineX"], m_profiles.at(m_currentProfile)[0]["cutLineY"]};
}

float ProfileManager::getFirstNoteOffset() {
    return m_profiles.at(m_currentProfile)[0]["firstNoteOffset"];
}

sf::Vector2f ProfileManager::getBreaks() {
    return sf::Vector2f{m_profiles.at(m_currentProfile)[0]["verticalBreak"], m_profiles.at(m_currentProfile)[0]["horizontalBreak"]};
}
