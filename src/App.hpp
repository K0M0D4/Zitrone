#pragma once

#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

namespace cmt {
    class App {
    public:
        App();

        int32_t start();

    private:
        sf::RenderWindow m_window;

        sf::Text m_testText;

        ResourceManager m_resources;

        /*
        Texture IDs:

        Font IDs:
            0 -> PlayfairDisplay
        */
    };
}