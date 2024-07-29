#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include <map>

using json = nlohmann::json;

class ProfileManager {
public:
    ProfileManager();

    void load();

    void switchProfile(const std::string& profile);

    int getProfilesCount();
    std::string getName(int id);

    sf::Vector2f getPageSize();
    sf::Vector2f getCutLine();
    float getFirstNoteOffset();
    sf::Vector2f getBreaks();
    float getChordSize();

    void setPageSize(sf::Vector2f pageSize);
    void setCutLine(sf::Vector2f cutLine);
    void setFirstNoteOffset(float offset);
    void setBreaks(sf::Vector2f breaks);
    void setChordSize(float chordSize);

    void saveProfile(const std::string& oldName, const std::string& newName);

private:
    std::map<std::string, json> m_profiles{};
    std::map<int, std::string> m_profileNames{};
    std::string m_currentProfile{"default"};

    int m_profilesCount{};

    void changeName(const std::string& oldName, const std::string& newName);

};
