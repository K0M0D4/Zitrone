#pragma once

#include "Project.hpp"
#include "UI.hpp"

#include "fw/Button.hpp"
#include "fw/DashLine.hpp"
#include "fw/ResourceManager.hpp"

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

        Project m_project{};

        // viewport
        sf::View m_viewport{};
        sf::View m_normalView{};
        sf::Vector2i m_prevMousePos{};
        sf::Vector2i m_deltaMousePos{};
        bool m_wasMousePressed{};
        float m_vpzoom{1.0f};

        void update();
        void render();

        void saveAsDialog();
        void openDialog();
        void exportDialog();

        /*
        Texture IDs:
            0 -> edit
            1 -> delete

        Font IDs:
            0 -> PlayfairDisplay

        Theme IDs:
            0 -> dark
        */
    };
}