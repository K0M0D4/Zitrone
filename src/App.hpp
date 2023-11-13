#pragma once

#include "Config.hpp"
#include "Project.hpp"
#include "Settings.hpp"
#include "UI.hpp"

#include "fw/DashLine.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <array>
#include <vector>

class App {
public:
    App();

    int32_t start();

private:
    cmt::ResourceManager m_resources{};

    sf::RenderWindow m_window{};

    UI m_UI{};
    tgui::GuiSFML m_GUI;

    tgui::Button::Ptr m_saveBtn;
    tgui::Button::Ptr m_saveAsBtn;
    tgui::Button::Ptr m_exportBtn;
    tgui::Button::Ptr m_openBtn;
    tgui::Button::Ptr m_settingsBtn;

    tgui::Button::Ptr m_addNoteBtn;
    tgui::Button::Ptr m_deleteNoteBtn;
    std::array<tgui::Button::Ptr, 7> m_chordsBtns{};

    Project m_project{};

    Config m_config{};

    bool m_CTRLPressed{false};
    bool m_ShiftPressed{false};

    sf::Vector2i m_lastAL{};

    // viewport
    sf::View m_viewport{};
    sf::View m_normalView{};
    sf::Vector2i m_prevMousePos{};
    sf::Vector2i m_deltaMousePos{};
    bool m_wasMousePressed{};
    float m_vpzoom{1.0f};

    std::array<std::string, 5> m_languageData{};

    void update();
    void render();

    void saveAsDialog();
    void openDialog();
    void exportDialog();

    void calculateViewport();

    void processMouseInput(sf::Event& event);
    void processKeyboardInput(sf::Event& event);
    void processZoom(sf::Event& event);

    void recalculateVerticalBtns();

    void saveBtnPressed();
    void saveAsBtnPressed();
    void exportBtnPressed();
    void openBtnPressed();
    void settingsBtnPressed();

    void addNoteBtnPressed();
    void deleteNoteBtnPressed();
    void chordBtnPressed(uint16_t chord);

    void initButtons();
    void setupBtnsNames();
    void setupBtnsLook();
    void setupBtnsBehaviour();

    void loadLanguage(const std::string& filepath);

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
