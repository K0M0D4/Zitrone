#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class ProfileEditor {
public:
    ProfileEditor();

    void start();

private:
    sf::RenderWindow m_window{};

    tgui::GuiSFML m_GUI;

};
