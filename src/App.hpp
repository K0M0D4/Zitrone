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
        sf::RenderWindow m_window{};

        Button m_newBtn{};
        Button m_saveBtn{};
        Button m_exportBtn{};
        Button m_loadBtn{};
        Button m_settingsBtn{};

        Button m_imageBtnTest{};

        ResourceManager m_resources{};

        /*
        Texture IDs:
            0 -> dot

        Font IDs:
            0 -> PlayfairDisplay
        */
    };
}