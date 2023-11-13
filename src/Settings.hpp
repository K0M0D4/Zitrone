#pragma once

#include "Config.hpp"

#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

class Settings {
public:
    Settings();

    static void start(sf::RenderWindow& window);

private:

    static bool update(sf::RenderWindow& window);
    static void render(sf::RenderWindow& target);
};
