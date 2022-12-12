#pragma once

#include "fw/Button.hpp"
#include "fw/DashLine.hpp"
#include "fw/ResourceManager.hpp"

#include "Grid.hpp"
#include "UI.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace cmt {
    class App {
    public:
        App();

        int32_t start();

    private:
        ResourceManager m_resources{};

        sf::RenderWindow m_window{};

        UI m_UI{};

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
        float m_breakBetweenNotesV{0.5f * m_dpcm};
        float m_breakBetweenNotesH{0.9f * m_dpcm};

        Grid m_grid{m_workspace.getSize(), m_breakBetweenNotesV,
            m_breakBetweenNotesH, m_firstNoteOffset};

        void update();
        void render();

        /*
        Texture IDs:
            0 -> dot
            1 -> move

        Font IDs:
            0 -> PlayfairDisplay
        */
    };
}