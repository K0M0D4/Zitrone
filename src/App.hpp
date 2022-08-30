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

        ResourceManager m_resources;

        /*
        Texture IDs:

        Font IDs:
        
        */
    };
}