#pragma once

#include "fw/Button.hpp"
#include "fw/ImageButton.hpp"
#include "fw/ResourceManager.hpp"
#include "fw/TextButton.hpp"

#include <SFML/Graphics.hpp>

namespace cmt {
    class App {
    public:
        App();

        int32_t start();

    private:
        sf::RenderWindow m_window{};

        ImageButton m_testImageBtn{};

        TextButton m_plusBtn{};
        TextButton m_minusBtn{};

        ResourceManager m_resources{};

        /*
        Texture IDs:
            0 -> dot

        Font IDs:
            0 -> PlayfairDisplay
        */
    };
}