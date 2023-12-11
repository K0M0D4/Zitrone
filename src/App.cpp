#include "App.hpp"

#include <nfd.h>

#include <fstream>

App::App() {
    m_profiles.load();
    m_profiles.switchProfile("default.json");

    m_window.create(sf::VideoMode(1280, 720), "Zitrone");
    m_window.setVerticalSyncEnabled(true);

    m_GUI.setTarget(m_window);

    m_resources.loadTheme("res/themes/" + m_config.getTheme() + "/theme.json");
    
    m_resources.loadTexture("res/themes/" + m_config.getTheme() + "/"
        + m_resources.getTheme(0).getAddNoteBtnImgFilepath());
    m_resources.loadTexture("res/themes/" + m_config.getTheme() + "/"
        + m_resources.getTheme(0).getDeleteNoteBtnImgFilepath());
    m_resources.loadTexture("res/themes/" + m_config.getTheme() + "/"
        + m_resources.getTheme(0).getChangeChordPosBtnImgFilepath());

    m_resources.loadTexture("res/arrow-TL.png");
    m_resources.loadTexture("res/arrow-T.png");
    m_resources.loadTexture("res/arrow-TR.png");
    m_resources.loadTexture("res/arrow-L.png");
    m_resources.loadTexture("res/arrow-R.png");
    m_resources.loadTexture("res/arrow-DL.png");
    m_resources.loadTexture("res/arrow-D.png");
    m_resources.loadTexture("res/arrow-DR.png");

    m_resources.loadTexture("res/themes/" + m_config.getTheme() + "/"
        + m_resources.getTheme(0).getArrowUpImgFilepath());
    
    m_resources.loadFont("res/Manrope-Medium.ttf");

    tgui::Theme::setDefault("res/themes/" + m_config.getTheme() + "/"
        + m_resources.getTheme(0).getTGUIFilepath());

    m_project = Project(&m_profiles, &m_resources);

    loadLanguage(m_config.getLang());

    initButtons();

    calculateViewport();
}

int32_t App::start() {
    NFD_Init();

    while(m_window.isOpen()) {
        update();
        render();
        m_window.display();
    }

    NFD_Quit();

    return 0;
}

void App::update() {
    sf::Vector2i winMousePos{sf::Mouse::getPosition(m_window)};

    sf::Event event;
    while(m_window.pollEvent(event)) {
        m_GUI.handleEvent(event);

        if(event.type == sf::Event::Closed) {
            m_window.close();
        }

        if(event.type == sf::Event::Resized) {
            calculateViewport();
        }

        if(!m_isChordPosModeOn) {
            if(event.type == sf::Event::MouseWheelScrolled
                && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                
                processZoom(event);
            }

            if(event.type == sf::Event::MouseButtonPressed)
                processMouseInput(event);
        }

        if(event.type == sf::Event::KeyPressed) {
            processKeyboardInput(event);
        }

        if(event.type == sf::Event::KeyReleased) {
            if(event.key.code == sf::Keyboard::LControl)
                m_CTRLPressed = false;

            if(event.key.code == sf::Keyboard::LShift)
                m_ShiftPressed = false;
        }
    }

    if(m_window.hasFocus()) {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) 
            && winMousePos.y > m_UpBarSize
            && winMousePos.x < m_window.getSize().x - m_VerBarSize
            && winMousePos.y < m_window.getSize().y - m_DownBarSize
            && winMousePos.x > 0.0f && winMousePos.y < m_window.getSize().y) {
            
            if(m_wasMousePressed) {
                m_deltaMousePos = winMousePos - m_prevMousePos;
            }
            m_prevMousePos = winMousePos;
            m_wasMousePressed = true;
        } else {
            m_wasMousePressed = false;
            m_prevMousePos = sf::Vector2i{};
            m_deltaMousePos = sf::Vector2i{};
        }

        if(!m_isChordPosModeOn) {
            m_viewport.move(static_cast<float>(-m_deltaMousePos.x) * m_vpzoom,
                static_cast<float>(-m_deltaMousePos.y) * m_vpzoom);
        }
    }
}

void App::render() {
    m_window.clear(m_resources.getTheme(0).getBgColor());

    // viewport
    m_window.setView(m_viewport);
    m_project.render(m_window);

    // UI
    m_window.setView(m_normalView);
    m_GUI.draw();
}

void App::saveAsDialog() {
    nfdchar_t* savePath{};

    nfdfilteritem_t filterItem[1] {{"Project files", "ztp"}};

    nfdresult_t result{NFD_SaveDialog(&savePath, filterItem, 1, NULL, "project.ztp")};
    
    if(result == NFD_OKAY) {
        m_project.saveAs(savePath);
        NFD_FreePath(savePath);
    } else if(result != NFD_CANCEL) {
        throw std::runtime_error("Internal error: "
            + std::string{NFD_GetError()} + '\n');
    }
}

void App::openDialog() {
    nfdchar_t* openPath{};

    nfdfilteritem_t filterItem[1] {{"Project files", "ztp"}};

    nfdresult_t result{NFD_OpenDialog(&openPath, filterItem, 1, NULL)};
    
    if(result == NFD_OKAY) {
        m_project.open(openPath);
        NFD_FreePath(openPath);
    } else if(result != NFD_CANCEL) {
        throw std::runtime_error("Internal error: "
            + std::string{NFD_GetError()} + '\n');
    }
}

void App::exportDialog() {
    nfdchar_t* exportPath{};

    nfdfilteritem_t filterItem[1] {{"Image", "png"}};

    nfdresult_t result{NFD_SaveDialog(&exportPath, filterItem, 1, NULL, "project.png")};
    
    if(result == NFD_OKAY) {
        m_project.exportProj(exportPath);
        NFD_FreePath(exportPath);
    } else if(result != NFD_CANCEL) {
        throw std::runtime_error("Internal error: "
            + std::string{NFD_GetError()} + '\n');
    }
}

void App::calculateViewport() {
    sf::Vector2f vpcenter = m_viewport.getCenter();
    m_viewport = sf::View(sf::FloatRect(0.f, 0.f,
        m_window.getSize().x - m_VerBarSize,
        m_window.getSize().y - m_UpBarSize - m_DownBarSize));
    m_viewport.setCenter(vpcenter);

    m_viewport.setViewport(sf::FloatRect(0.0f,
        1.0f - (m_window.getSize().y - m_UpBarSize) / m_window.getSize().y,
        (m_window.getSize().x - m_VerBarSize) / m_window.getSize().x,
        (m_window.getSize().y - m_UpBarSize - m_DownBarSize) / m_window.getSize().y));
    
    m_normalView = sf::View(sf::FloatRect(0.f, 0.f,
        m_window.getSize().x, m_window.getSize().y));
    
    m_vpzoom = 1.0f;

    recalculateVerticalBtns();
    recalculateDownBtns();
}

void App::processMouseInput(sf::Event& event) {
    sf::Vector2i winMousePos{sf::Mouse::getPosition(m_window)};
    sf::Vector2f vpMousePos{m_window.mapPixelToCoords(winMousePos, m_viewport)};

    if(winMousePos.y > m_UpBarSize
        && winMousePos.x < m_window.getSize().x - m_VerBarSize
        && winMousePos.y < m_window.getSize().y - m_DownBarSize) {
        
        m_project.setActiveLines(vpMousePos);
        m_lastAL = m_project.getActiveLines();
    }
}

void App::processKeyboardInput(sf::Event& event) {
    sf::Keyboard::Key key{event.key.code};

    if(!m_isChordPosModeOn) {
        switch(key) {
        case sf::Keyboard::Space:
            m_project.addNote();
            m_lastAL = m_project.getActiveLines();
            m_project.moveActiveLines(sf::Vector2i(0, 1)); break;
        case sf::Keyboard::Backspace:
        case sf::Keyboard::Delete:
            m_project.deleteNote(); break;
        case sf::Keyboard::Right:
            if(m_CTRLPressed) {
                m_project.moveNotesRight();
            } else {
                m_lastAL = m_project.moveActiveLines(sf::Vector2i(1, 0));
            } break;
        case sf::Keyboard::Left:
            if(m_CTRLPressed) {
                m_project.moveNotesLeft();
            } else {
                m_lastAL = m_project.moveActiveLines(sf::Vector2i(-1, 0));
            } break;
        case sf::Keyboard::Up:
            if(m_CTRLPressed) {
                m_project.moveNotesUp();
            } else {
                m_lastAL = m_project.moveActiveLines(sf::Vector2i(0, -1));
            } break;
        case sf::Keyboard::Down:
            if(m_CTRLPressed) {
                m_project.moveNotesDown();
            } else {
                m_lastAL = m_project.moveActiveLines(sf::Vector2i(0, 1));
            } break;
        case sf::Keyboard::Equal:
        case sf::Keyboard::Hyphen:
            processZoom(event); break;
        case sf::Keyboard::LControl:
            m_CTRLPressed = true; break;
        case sf::Keyboard::LShift:
            m_ShiftPressed = true; break;
        case sf::Keyboard::S:
            if(m_CTRLPressed) {
                if(m_ShiftPressed
                    || m_project.getName() == std::string{}) {

                    saveAsDialog();
                    break;
                }

                m_project.save();
            } break;
        case sf::Keyboard::O:
            if(m_CTRLPressed)
                openDialog(); break;
        case sf::Keyboard::E:
            if(m_CTRLPressed)
                exportDialog(); break;
        }
    }

    if(key == sf::Keyboard::C) {
        if(m_isChordPosModeOn) {
            m_isChordPosModeOn = false;
            enableChordPosSetBtns(false);
        } else if(m_project.isALValidforChordPos() && !m_isChordPosModeOn) {
            m_isChordPosModeOn = true;
            enableChordPosSetBtns(true);
        }
    }
        
    if(key >= sf::Keyboard::Num0
        && key <= sf::Keyboard::Num6) {

        sf::Vector2i ALbuf{m_project.getActiveLines()};
    
        m_project.setActiveLines(m_lastAL);
        m_project.setChord(key - 26);

        m_project.setActiveLines(ALbuf);
        
    } else if(key >= sf::Keyboard::Numpad0
        && key <= sf::Keyboard::Numpad6) {

        if(!m_isChordPosModeOn) {
            sf::Vector2i ALbuf{m_project.getActiveLines()};
        
            m_project.setActiveLines(m_lastAL);
            m_project.setChord(key - 75);

            m_project.setActiveLines(ALbuf);
        } 

    }
    
    if(key >= sf::Keyboard::Numpad0
        && key <= sf::Keyboard::Numpad9) {
        if(m_isChordPosModeOn) {
            m_project.setChordPosition(key - 75);
            enableChordPosSetBtns(false);
            m_isChordPosModeOn = false;
        }
    }
}

void App::processZoom(sf::Event& event) {
    if(event.key.code == sf::Keyboard::Equal && m_vpzoom > 0.78f) {
        m_viewport.zoom(0.96f);
        m_vpzoom *= 0.96f;
    } else if(event.key.code == sf::Keyboard::Hyphen) {
        m_viewport.zoom(1.04f);
        m_vpzoom *= (1.04f);
    } else if(event.mouseWheelScroll.delta > 0 && m_vpzoom > 0.78f) {
        m_viewport.zoom(0.96f);
        m_vpzoom *= 0.96f;
    } else if(event.mouseWheelScroll.delta < 0) {
        m_viewport.zoom(1.04f);
        m_vpzoom *= (1.04f);
    }
}

void App::recalculateVerticalBtns() {
    float xVerBtnsPos = static_cast<float>(m_window.getSize().x) - 50;

    m_addNoteBtn->setPosition(xVerBtnsPos, 40);

    m_deleteNoteBtn->setPosition({bindLeft(m_addNoteBtn),
        bindBottom(m_addNoteBtn) + 15});

    m_chordPosBtn->setPosition({bindLeft(m_addNoteBtn),
        bindBottom(m_deleteNoteBtn) + 15});

    m_chordsBtns.at(0)->setPosition({bindLeft(m_addNoteBtn),
        bindBottom(m_chordPosBtn) + 15});

    for(uint16_t c{0}; c < m_chordsBtns.size() - 1; ++c) {
        m_chordsBtns.at(c + 1)->setPosition({bindLeft(m_addNoteBtn),
            bindBottom(m_chordsBtns.at(c)) + 10});
    }
}

void App::recalculateDownBtns() {
    m_profilesLabel->setPosition(0, m_window.getSize().y - 33);
    m_currentProfileLabel->setPosition({bindRight(m_profilesLabel) + 5}, m_window.getSize().y - 33);
    m_profileSwitcher->setPosition({bindRight(m_currentProfileLabel) + 5}, m_window.getSize().y - 33);
}

void App::saveBtnPressed() {
    m_project.getName() == std::string{} ? saveAsDialog() : m_project.save();
}

void App::saveAsBtnPressed() {
    saveAsDialog();
}

void App::exportBtnPressed() {
    exportDialog();
}

void App::openBtnPressed() {
    openDialog();
}

void App::settingsBtnPressed() {
    //Settings::start(m_window);
}

void App::addNoteBtnPressed() {
    m_project.addNote();
    m_lastAL = m_project.getActiveLines();
    m_project.moveActiveLines(sf::Vector2i(0, 1));
}

void App::deleteNoteBtnPressed() {
    m_project.deleteNote();
}

void App::chordPosBtnPressed() {
    if(m_isChordPosModeOn) {
        m_isChordPosModeOn = false;
        enableChordPosSetBtns(false);
    } else if(m_project.isALValidforChordPos() && !m_isChordPosModeOn) {
        m_isChordPosModeOn = true;
        enableChordPosSetBtns(true);
    }
}

void App::chordBtnPressed(uint16_t chord) {
    sf::Vector2i ALbuf{m_project.getActiveLines()};

    m_project.setActiveLines(m_lastAL);
    m_project.setChord(chord);
    m_project.setActiveLines(ALbuf);
}

void App::chordPosSetBtnPressed(uint16_t position) {
    m_project.setChordPosition(position);
    m_isChordPosModeOn = false;
    enableChordPosSetBtns(false);
}

void App::initButtons() {
    setupBtnsNames();
    setupTooltips();
    setupBtnsLook();
    setupBtnsBehaviour();

    setupChordsBtns();
    setupChordPosSetBtns();

    enableChordPosSetBtns(false);
}

void App::setupBtnsNames() {
    setupUpBtnsNames();
    setupVerBtnsNames();
    setupDownBtnsNames();
}

void App::setupUpBtnsNames() {
    m_saveBtn = tgui::Button::create(m_languageData.at(0));
    m_saveAsBtn = tgui::Button::create(m_languageData.at(1));
    m_exportBtn = tgui::Button::create(m_languageData.at(2));
    m_openBtn = tgui::Button::create(m_languageData.at(3));
    m_settingsBtn = tgui::Button::create(m_languageData.at(4));
}

void App::setupVerBtnsNames() {
    m_addNoteBtn = tgui::Button::create();
    m_deleteNoteBtn = tgui::Button::create();
    m_chordPosBtn = tgui::Button::create();
}

void App::setupDownBtnsNames() {
    m_profilesLabel = tgui::Button::create(m_languageData.at(8));
    m_currentProfileLabel = tgui::Button::create("default");
    m_profileSwitcher = tgui::Button::create();
}

void App::setupBtnsLook() {
    setupUpBtnsLook();
    setupVerBtnsLook();
    setupDownBtnsLook();
}

void App::setupUpBtnsLook() {
    m_saveBtn->setPosition(5, 5);
    m_saveBtn->setSize(100, 25);
    m_saveBtn->setTextSize(17);
    m_GUI.add(m_saveBtn);

    m_saveAsBtn->setPosition({bindRight(m_saveBtn) + 5.0f, bindTop(m_saveBtn)});
    m_saveAsBtn->setSize(bindSize(m_saveBtn));
    m_saveAsBtn->setTextSize(17);
    m_GUI.add(m_saveAsBtn);

    m_exportBtn->setPosition({bindRight(m_saveAsBtn) + 5.0f, bindTop(m_saveBtn)});
    m_exportBtn->setSize(bindSize(m_saveBtn));
    m_exportBtn->setTextSize(17);
    m_GUI.add(m_exportBtn);

    m_openBtn->setPosition({bindRight(m_exportBtn) + 5.0f, bindTop(m_saveBtn)});
    m_openBtn->setSize(bindSize(m_saveBtn));
    m_openBtn->setTextSize(17);
    m_GUI.add(m_openBtn);

    m_settingsBtn->setPosition({bindRight(m_openBtn) + 5.0f, bindTop(m_saveBtn)});
    m_settingsBtn->setSize(bindSize(m_saveBtn));
    m_settingsBtn->setTextSize(17);
    m_GUI.add(m_settingsBtn);
}

void App::setupVerBtnsLook() {
    m_addNoteBtn->getRenderer()->setTexture(m_resources.getTexture(0));
    m_addNoteBtn->setSize(40, 40);
    m_GUI.add(m_addNoteBtn);

    m_deleteNoteBtn->getRenderer()->setTexture(m_resources.getTexture(1));
    m_deleteNoteBtn->setSize(bindSize(m_addNoteBtn));
    m_GUI.add(m_deleteNoteBtn);
    
    m_chordPosBtn->getRenderer()->setTexture(m_resources.getTexture(2));
    m_chordPosBtn->setSize(bindSize(m_addNoteBtn));
    m_GUI.add(m_chordPosBtn);
}

void App::setupDownBtnsLook() {
    m_profilesLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_profilesLabel->setSize(80, 25);
    m_profilesLabel->setTextSize(17);
    m_GUI.add(m_profilesLabel);

    m_currentProfileLabel->setSize(200, 25);
    m_currentProfileLabel->setTextSize(17);
    m_GUI.add(m_currentProfileLabel);

    m_profileSwitcher->getRenderer()->setTexture(m_resources.getTexture(11));
    m_profileSwitcher->setSize(40, 40);
    m_GUI.add(m_profileSwitcher);
}

void App::setupBtnsBehaviour() {
    setupUpBtnsBehaviour();
    setupVerBtnsBehaviour();
}

void App::setupUpBtnsBehaviour() {
    m_saveBtn->onPress(&saveBtnPressed, this);
    m_saveAsBtn->onPress(&saveAsBtnPressed, this);
    m_exportBtn->onPress(&exportBtnPressed, this);
    m_openBtn->onPress(&openBtnPressed, this);
    m_settingsBtn->onPress(&settingsBtnPressed, this);
}

void App::setupVerBtnsBehaviour() {
    m_addNoteBtn->onPress(&addNoteBtnPressed, this);
    m_deleteNoteBtn->onPress(&deleteNoteBtnPressed, this);
    m_chordPosBtn->onPress(&chordPosBtnPressed, this);
}

void App::setupDownBtnsBehaviour() {

}

void App::setupChordsBtns() {
    for(uint16_t c{}; c < m_chordsBtns.size(); ++c) {
        m_chordsBtns.at(c) = tgui::Button::create();
        m_chordsBtns.at(c)->setSize(bindSize(m_addNoteBtn));
        m_chordsBtns.at(c)->setTextSize(32);
        m_GUI.add(m_chordsBtns.at(c));

        m_chordsBtns.at(c)->setText(std::to_string(c));
        m_chordsBtns.at(c)->onPress(&chordBtnPressed, this, c);
    }
}

void App::setupChordPosSetBtns() {
    m_chordPosSetBtnsVerLayout = tgui::VerticalLayout::create();
    m_chordPosSetBtnsVerLayout->setSize(240, 240);
    m_GUI.add(m_chordPosSetBtnsVerLayout);

    m_chordPosSetBtnsVerLayout->setPosition(520, 240);

    for(int i{}; i < 3; ++i) {
        m_chordPosSetBtnsHorLayouts.at(i) = tgui::HorizontalLayout::create();
        m_chordPosSetBtnsHorLayouts.at(i)->setSize(240, 80);
        m_chordPosSetBtnsVerLayout->add(m_chordPosSetBtnsHorLayouts.at(i));
    }

    for(uint16_t c{}; c < m_chordPosSetBtns.size() + 1; ++c) {
        if(c == 4) ++c;
        if(c < 4) {
            m_chordPosSetBtns.at(c) = tgui::Button::create();
            m_chordPosSetBtns.at(c)->getRenderer()->setTexture(m_resources.getTexture(c + 3));
            m_chordPosSetBtnsHorLayouts.at(c / 3)->add(m_chordPosSetBtns.at(c));
        } else if(c > 4) {
            m_chordPosSetBtns.at(c - 1) = tgui::Button::create();
            m_chordPosSetBtns.at(c - 1)->getRenderer()->setTexture(m_resources.getTexture(c + 2));
            m_chordPosSetBtnsHorLayouts.at(c / 3)->add(m_chordPosSetBtns.at(c - 1));
        }
    }

    m_chordPosSetBtns.at(0)->onPress(&chordPosSetBtnPressed, this, 7);
    m_chordPosSetBtns.at(1)->onPress(&chordPosSetBtnPressed, this, 8);
    m_chordPosSetBtns.at(2)->onPress(&chordPosSetBtnPressed, this, 9);
    m_chordPosSetBtns.at(3)->onPress(&chordPosSetBtnPressed, this, 4);
    m_chordPosSetBtns.at(4)->onPress(&chordPosSetBtnPressed, this, 6);
    m_chordPosSetBtns.at(5)->onPress(&chordPosSetBtnPressed, this, 1);
    m_chordPosSetBtns.at(6)->onPress(&chordPosSetBtnPressed, this, 2);
    m_chordPosSetBtns.at(7)->onPress(&chordPosSetBtnPressed, this, 3);

    m_chordPosSetBtnsHorLayouts.at(1)->insertSpace(1, 1.0f);
}

void App::enableChordPosSetBtns(bool enable) {
    float newX{m_project.getNotePosAtAL().x};
    float newY{m_project.getNotePosAtAL().y};

    sf::Vector2i newPos{m_window.mapCoordsToPixel(sf::Vector2f(newX, newY), m_viewport)};
    newPos.x -= 120;
    newPos.y -= 120;

    m_chordPosSetBtnsVerLayout->setPosition(newPos.x, newPos.y);

    m_chordPosSetBtnsVerLayout->setEnabled(enable);
    m_chordPosSetBtnsVerLayout->setVisible(enable);
}

void App::setupTooltips() {
    m_saveBtnTT = tgui::Label::create("(Ctrl + S)");
    m_saveBtnTT->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));
    m_saveBtn->setToolTip(m_saveBtnTT);

    m_saveAsBtnTT = tgui::Label::create("(Ctrl + Shift + S)");
    m_saveAsBtnTT->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));
    m_saveAsBtn->setToolTip(m_saveAsBtnTT);

    m_exportBtnTT = tgui::Label::create("(Ctrl + E)");
    m_exportBtnTT->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));
    m_exportBtn->setToolTip(m_exportBtnTT);

    m_openBtnTT = tgui::Label::create("(Ctrl + O)");
    m_openBtnTT->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));
    m_openBtn->setToolTip(m_openBtnTT);

    m_addNoteBtnTT = tgui::Label::create(m_languageData.at(5) + " (Space)");
    m_addNoteBtnTT->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));
    m_addNoteBtn->setToolTip(m_addNoteBtnTT);

    m_deleteNoteBtnTT = tgui::Label::create(m_languageData.at(6) + " (Delete) (Backspace)");
    m_deleteNoteBtnTT->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));
    m_deleteNoteBtn->setToolTip(m_deleteNoteBtnTT);

    m_chordPosBtnTT = tgui::Label::create(m_languageData.at(7) + " (C)");
    m_chordPosBtnTT->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));
    m_chordPosBtn->setToolTip(m_chordPosBtnTT);
}

void App::loadLanguage(const std::string& filepath) {
    std::ifstream file("res/languages/" + filepath + ".txt");
    if(!file.good())
        throw std::runtime_error("Error: Can't read language: "
            + filepath + '\n');

    for(uint16_t i{}; i < m_languageData.size(); ++i) {
        getline(file, m_languageData.at(i));
    }
}
