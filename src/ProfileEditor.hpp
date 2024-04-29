#pragma once

#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <vector>
#include <string>

class ProfileEditor {
public:
    ProfileEditor();

    void start(cmt::ResourceManager& resources,
        std::vector<std::string>& languageData);

private:
    sf::RenderWindow m_window{};

    tgui::GuiSFML m_GUI;

    cmt::ResourceManager* m_resources{};
    std::vector<std::string>* m_languageData{};

    tgui::Button::Ptr m_pageWidthLabel;
    tgui::Button::Ptr m_pageHeightLabel;
    tgui::Button::Ptr m_cutLineXLabel;
    tgui::Button::Ptr m_cutLineYLabel;
    tgui::Button::Ptr m_verticalBreakLabel;
    tgui::Button::Ptr m_horizontalBreakLabel;
    tgui::Button::Ptr m_firstNoteOffsetLabel;

    tgui::EditBox::Ptr m_pageWidthInput;
    tgui::EditBox::Ptr m_pageHeightInput;
    tgui::EditBox::Ptr m_cutLineXInput;
    tgui::EditBox::Ptr m_cutLineYInput;
    tgui::EditBox::Ptr m_verticalBreakInput;
    tgui::EditBox::Ptr m_horizontalBreakInput;
    tgui::EditBox::Ptr m_firstNoteOffsetInput;

    tgui::Picture::Ptr m_helperImage;

    tgui::Button::Ptr m_currentProfileLabel;

    tgui::ScrollablePanel::Ptr m_profilesList;
    std::vector<tgui::Button::Ptr> m_profileSwitchers{};

    tgui::Button::Ptr m_saveAsBtn;
    tgui::Button::Ptr m_saveBtn;

    void update();
    void render();

};
