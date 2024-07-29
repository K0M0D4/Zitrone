#include "ProfileManager.hpp"

#include <fstream>
#include <cstdlib>

ProfileManager::ProfileManager() {

}

void ProfileManager::load() {
    std::ifstream profilesList{"res/profiles/list.app.json"};
    if(!profilesList.good())
        throw std::runtime_error("Error: Can't load profiles list file\n");

    json list{json::parse(profilesList)};

    m_profilesCount = list[0].at("profiles").size();
    m_profiles.clear();
    m_profileNames.clear();
    
    for(int i{}; i < list[0].at("profiles").size(); ++i) {
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

float ProfileManager::getChordSize() {
    return m_profiles.at(m_currentProfile)[0]["chordSize"];
}

void ProfileManager::setPageSize(sf::Vector2f pageSize) {
    m_profiles.at(m_currentProfile)[0]["pageWidth"] = pageSize.x;
    m_profiles.at(m_currentProfile)[0]["pageHeight"] = pageSize.y;
}

void ProfileManager::setCutLine(sf::Vector2f cutLine) {
    m_profiles.at(m_currentProfile)[0]["cutLineX"] = cutLine.x;
    m_profiles.at(m_currentProfile)[0]["cutLineY"] = cutLine.y;
}

void ProfileManager::setFirstNoteOffset(float offset) {
    m_profiles.at(m_currentProfile)[0]["firstNoteOffset"] = offset;
}

void ProfileManager::setBreaks(sf::Vector2f breaks) {
    m_profiles.at(m_currentProfile)[0]["verticalBreak"] = breaks.x;
    m_profiles.at(m_currentProfile)[0]["horizontalBreak"] = breaks.y;
}

void ProfileManager::setChordSize(float chordSize) {
    m_profiles.at(m_currentProfile)[0]["chordSize"] = chordSize;
}

void ProfileManager::saveProfile(const std::string& oldName, const std::string& newName) {
    changeName(oldName, newName);

    std::string oldFilename{"res/profiles/" + oldName + ".json"};
    std::remove(oldFilename.c_str());

    std::ofstream profileFile{"res/profiles/" + newName + ".json", std::ios::trunc};

    std::string profileData{"{\n"};
    profileData += "\"pageWidth\": " + std::to_string((float)m_profiles.at(m_currentProfile)[0]["pageWidth"]) + ",\n";
    profileData += "\"pageHeight\": " + std::to_string((float)m_profiles.at(m_currentProfile)[0]["pageHeight"]) + ",\n";
    profileData += "\"cutLineX\": " + std::to_string((float)m_profiles.at(m_currentProfile)[0]["cutLineX"]) + ",\n";
    profileData += "\"cutLineY\": " + std::to_string((float)m_profiles.at(m_currentProfile)[0]["cutLineY"]) + ",\n";
    profileData += "\"firstNoteOffset\": " + std::to_string((float)m_profiles.at(m_currentProfile)[0]["firstNoteOffset"]) + ",\n";
    profileData += "\"verticalBreak\": " + std::to_string((float)m_profiles.at(m_currentProfile)[0]["verticalBreak"]) + ",\n";
    profileData += "\"horizontalBreak\": " + std::to_string((float)m_profiles.at(m_currentProfile)[0]["horizontalBreak"]) + "\n}\n";

    profileFile << profileData << std::flush;

    profileFile.close();

    std::ofstream profilesListFile{"res/profiles/list.app.json", std::ios::trunc};
    std::string listData{"{\n"};
    listData += "\"profiles\": [";
    for(int i{}; i < m_profilesCount; ++i) {
        listData += "\"" + m_profileNames[i] + "\"";
        if(i + 1 < m_profilesCount) {
            listData += ", ";
        }
    } 
    listData += "]\n}\n";

    profilesListFile << listData << std::flush;

    profilesListFile.close();

    load();
}

void ProfileManager::changeName(const std::string& oldName, const std::string& newName) {
    for(int i{}; i < m_profilesCount; ++i) {
        if(getName(i) == oldName) {
            m_profileNames[i] = newName;
            break;
        }
    }

    m_profiles[newName] = m_profiles[oldName];
    
    if(m_profiles.find(oldName) != m_profiles.end() && oldName != newName) {
        m_profiles.erase(m_profiles.find(oldName));
    }

    m_currentProfile = newName;
}
