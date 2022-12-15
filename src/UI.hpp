#pragma once

#include "fw/Button.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Window.hpp>

namespace cmt {
    class UI {
    public:
        UI();

        void init(ResourceManager& resources);

        void render(sf::RenderWindow& target);

        void recalculate(sf::RenderWindow& window);

        // horizontal navbar
        TextButton m_saveBtn{};
        TextButton m_exportBtn{};
        TextButton m_openBtn{};
        TextButton m_settingsBtn{};

        // vertical navbar
        ImageButton m_moveButton{};
        ImageButton m_noteBtn{};
        std::array<TextButton, 6> m_chBtn{};

    private:
        void initHNavBar(ResourceManager& resources);
        void initVNavBar(ResourceManager& resources);

    };
}