#pragma once

#include "Config.hpp"
#include "Project.hpp"
#include "Settings.hpp"

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

    // members

    cmt::ResourceManager m_resources{};

    sf::RenderWindow m_window{};

    float m_HorBarSize{37};
    float m_VerBarSize{60};

    // GUI
    tgui::GuiSFML m_GUI;

    // buttons
    tgui::Button::Ptr m_saveBtn;
    tgui::Button::Ptr m_saveAsBtn;
    tgui::Button::Ptr m_exportBtn;
    tgui::Button::Ptr m_openBtn;
    tgui::Button::Ptr m_settingsBtn;

    tgui::Button::Ptr m_addNoteBtn;
    tgui::Button::Ptr m_deleteNoteBtn;
    tgui::Button::Ptr m_chordPosBtn;
    std::array<tgui::Button::Ptr, 7> m_chordsBtns{};

    tgui::VerticalLayout::Ptr m_chordPosSetBtnsVerLayout;
    std::array<tgui::HorizontalLayout::Ptr, 3> m_chordPosSetBtnsHorLayouts;
    std::array<tgui::Button::Ptr, 8> m_chordPosSetBtns{};

    // tooltips
    tgui::Label::Ptr m_saveBtnTT;
    tgui::Label::Ptr m_saveAsBtnTT;
    tgui::Label::Ptr m_exportBtnTT;
    tgui::Label::Ptr m_openBtnTT;

    tgui::Label::Ptr m_addNoteBtnTT;
    tgui::Label::Ptr m_deleteNoteBtnTT;

    Project m_project{};

    Config m_config{};

    bool m_CTRLPressed{false};
    bool m_ShiftPressed{false};

    bool m_isChordPosModeOn{false};

    sf::Vector2i m_lastAL{};

    // viewport
    sf::View m_viewport{};
    sf::View m_normalView{};
    sf::Vector2i m_prevMousePos{};
    sf::Vector2i m_deltaMousePos{};
    bool m_wasMousePressed{};
    float m_vpzoom{1.0f};

    std::array<std::string, 5> m_languageData{};

    // methods

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
    void chordPosBtnPressed();
    void chordBtnPressed(uint16_t chord);

    void initButtons();

    void setupBtnsNames();

    void setupHorBtnsNames();
    void setupVerBtnsNames();

    void setupBtnsLook();

    void setupHorBtnsLook();
    void setupVerBtnsLook();

    void setupBtnsBehaviour();

    void setupHorBtnsBehaviour();
    void setupVerBtnsBehaviour();

    void setupChordsBtns();
    void setupChordPosSetBtns();

    void setupTooltips();

    void loadLanguage(const std::string& filepath);

    /*
    Texture IDs:
        0 -> edit
        1 -> delete
        2 -> chord position
        3 - 11 -> arrows counting from top left clockwise

    Font IDs:
        0 -> Manrope
    */

};
