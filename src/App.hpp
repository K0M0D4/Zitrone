#pragma once

#include "fw/Button.hpp"
#include "fw/DashLine.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

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

        // viewport
        sf::View m_viewport{};
        sf::View m_normalView{};
        sf::Vector2i m_prevMousePos{};
        sf::Vector2i m_deltaMousePos{};
        bool m_wasMousePressed{};
        float m_vpzoom{1.0f};

        float m_dpcm{118.1102f};

        // values have to be in pixels, not centimeters
        // outline of the workspace
        sf::RectangleShape m_workspace{sf::Vector2f{21.0f * m_dpcm,
            29.7f * m_dpcm}};

        float m_firstNoteOffset{0.9f * m_dpcm};
        float m_breakBetweenNotesH{0.9f * m_dpcm};
        float m_breakBetweenNotesV{0.5f * m_dpcm};

        DashLine m_line{};

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