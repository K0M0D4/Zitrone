#pragma once

#include "fw/Button.hpp"
#include "fw/ImageButton.hpp"
#include "fw/ResourceManager.hpp"
#include "fw/TextButton.hpp"

#include <SFML/Graphics.hpp>

// debug
#include <cstdio>

namespace cmt {
    class App {
    public:
        App();

        int32_t start();

    private:
        sf::RenderWindow m_window{};

        // horizontal navbar
        TextButton m_saveBtn{};
        TextButton m_exportBtn{};
        TextButton m_openBtn{};
        TextButton m_settingsBtn{};

        // vertical buttons
        ImageButton m_noteBtn{};
        std::array<TextButton, 6> m_chBtn{};
        ImageButton m_moveButton{};

        ResourceManager m_resources{};

        /*
        Texture IDs:
            0 -> dot
            1 -> move

        Font IDs:
            0 -> PlayfairDisplay
        */
    };
}