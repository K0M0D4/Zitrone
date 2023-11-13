#include "App.hpp"

#include <nfd.h>

#include <fstream>

App::App() {
    m_window.create(sf::VideoMode(1280, 720), "Zitrone");
    m_window.setVerticalSyncEnabled(true);

    m_GUI.setTarget(m_window);
    
    m_resources.loadTexture("res/themes/" + m_config.getTheme() + "/edit.png");
    m_resources.loadTexture("res/themes/" + m_config.getTheme() + "/delete.png");
    
    m_resources.loadFont("res/Manrope-Medium.ttf");

    m_resources.loadTheme("res/themes/" + m_config.getTheme() + "/app");

    tgui::Theme::setDefault("res/themes/" + m_config.getTheme() + "/tgui");

    m_project = Project(&m_config, &m_resources);

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

        if(event.type == sf::Event::MouseWheelScrolled
            && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            
            processZoom(event);
        }

        if(event.type == sf::Event::MouseButtonPressed)
            processMouseInput(event);

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
            && winMousePos.y > m_HorBarSize
            && winMousePos.x < m_window.getSize().x - m_VerBarSize
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

        m_viewport.move(static_cast<float>(-m_deltaMousePos.x) * m_vpzoom,
            static_cast<float>(-m_deltaMousePos.y) * m_vpzoom);
    }
}

void App::render() {
    m_window.clear(m_resources.getTheme(0).getColor(0));

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
        m_window.getSize().y - m_HorBarSize));
    m_viewport.setCenter(vpcenter);

    m_viewport.setViewport(sf::FloatRect(0.0f,
        1.0f - (m_window.getSize().y - m_HorBarSize)
        / m_window.getSize().y,
        (m_window.getSize().x - m_VerBarSize)
        / m_window.getSize().x,
        (m_window.getSize().y - m_HorBarSize)
        / m_window.getSize().y));
    
    m_normalView = sf::View(sf::FloatRect(0.f, 0.f,
        m_window.getSize().x, m_window.getSize().y));
    
    m_vpzoom = 1.0f;

    recalculateVerticalBtns();
}

void App::processMouseInput(sf::Event& event) {
    sf::Vector2i winMousePos{sf::Mouse::getPosition(m_window)};
    sf::Vector2f vpMousePos{m_window.mapPixelToCoords(winMousePos, m_viewport)};

    if(winMousePos.y > m_HorBarSize
        && winMousePos.x < m_window.getSize().x - m_VerBarSize) {
        
        m_project.setActiveLines(vpMousePos);
        m_lastAL = m_project.getActiveLines();
    }
}

void App::processKeyboardInput(sf::Event& event) {
    sf::Keyboard::Key key{event.key.code};

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
        
    if(key >= sf::Keyboard::Num0
        && key <= sf::Keyboard::Num6) {
        
        sf::Vector2i ALbuf{m_project.getActiveLines()};
        
        m_project.setActiveLines(m_lastAL);
        m_project.setChord(key - 26);

        m_project.setActiveLines(ALbuf);
    } else if(key >= sf::Keyboard::Numpad0
        && key <= sf::Keyboard::Numpad6) {

        sf::Vector2i ALbuf{m_project.getActiveLines()};
        
        m_project.setActiveLines(m_lastAL);
        m_project.setChord(key - 75);

        m_project.setActiveLines(ALbuf);
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

    m_chordsBtns.at(0)->setPosition({bindLeft(m_addNoteBtn),
        bindBottom(m_deleteNoteBtn) + 15});

    for(uint16_t c{0}; c < m_chordsBtns.size() - 1; ++c) {
        m_chordsBtns.at(c + 1)->setPosition({bindLeft(m_addNoteBtn),
            bindBottom(m_chordsBtns.at(c)) + 10});
    }
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

void App::chordBtnPressed(uint16_t chord) {
    sf::Vector2i ALbuf{m_project.getActiveLines()};

    m_project.setActiveLines(m_lastAL);
    m_project.setChord(chord);
    m_project.setActiveLines(ALbuf);
}

void App::initButtons() {
    setupBtnsNames();
    setupBtnsLook();
    setupBtnsBehaviour();
}

void App::setupBtnsNames() {
    m_saveBtn = tgui::Button::create(m_languageData.at(0));
    m_saveAsBtn = tgui::Button::create(m_languageData.at(1));
    m_exportBtn = tgui::Button::create(m_languageData.at(2));
    m_openBtn = tgui::Button::create(m_languageData.at(3));
    m_settingsBtn = tgui::Button::create(m_languageData.at(4));

    m_addNoteBtn = tgui::Button::create();
    m_deleteNoteBtn = tgui::Button::create();
}

void App::setupBtnsLook() {
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

    m_addNoteBtn->getRenderer()->setTexture(m_resources.getTexture(0));
    m_addNoteBtn->setSize(40, 40);
    m_GUI.add(m_addNoteBtn);

    m_deleteNoteBtn->getRenderer()->setTexture(m_resources.getTexture(1));
    m_deleteNoteBtn->setSize(bindSize(m_addNoteBtn));
    m_GUI.add(m_deleteNoteBtn);

    for(uint16_t c{}; c < m_chordsBtns.size(); ++c) {
        m_chordsBtns.at(c) = tgui::Button::create();
        m_chordsBtns.at(c)->setSize(bindSize(m_addNoteBtn));
        m_chordsBtns.at(c)->setTextSize(32);
        m_GUI.add(m_chordsBtns.at(c));

        // should not be here but it is here for a bit of optimization
        //      the for loop is not repeated
        m_chordsBtns.at(c)->setText(std::to_string(c));
        m_chordsBtns.at(c)->onPress(&chordBtnPressed, this, c);
    }
}

void App::setupBtnsBehaviour() {
    m_saveBtn->onPress(&saveBtnPressed, this);
    m_saveAsBtn->onPress(&saveAsBtnPressed, this);
    m_exportBtn->onPress(&exportBtnPressed, this);
    m_openBtn->onPress(&openBtnPressed, this);
    m_settingsBtn->onPress(&settingsBtnPressed, this);

    m_addNoteBtn->onPress(&addNoteBtnPressed, this);
    m_deleteNoteBtn->onPress(&deleteNoteBtnPressed, this);
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
