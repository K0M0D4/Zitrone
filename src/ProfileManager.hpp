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

    sf::Vector2f getPageSize();
    sf::Vector2f getCutLine();
    float getFirstNoteOffset();
    sf::Vector2f getBreaks();

private:
    std::map<std::string, json> m_profiles{};
    std::string m_currentProfile{"default"};

};
