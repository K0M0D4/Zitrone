#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

class Config {
public:
    Config();

    void load();

    std::string getLang();
    std::string getTheme();

private:
    json m_config{};

};
