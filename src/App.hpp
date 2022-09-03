#pragma once

#include "fw/Button.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

namespace cmt {
    class App {
    public:
        App();

        int32_t start();

    private:
        sf::RenderWindow m_window;

        sf::Text m_testText;

        Button m_testButton;

        ResourceManager m_resources;

        /*
        Texture IDs:

        Font IDs:
            0 -> PlayfairDisplay
        */
    };
}