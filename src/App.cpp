#include "App.hpp"

#include <nfd.h>

#include <fstream>

App::App() {
    m_window.create(sf::VideoMode(1280, 720), "Zitrone");
    m_window.setVerticalSyncEnabled(true);
    
    m_resources.loadTexture("res/edit.png");
    m_resources.loadTexture("res/delete.png");
    
    m_resources.loadFont("res/PlayfairDisplay.ttf");

    m_resources.loadTheme("res/themes/" + m_config.getTheme());

    m_project = Project(&m_config, &m_resources);
    
    m_UI = UI{m_resources, m_config.getLang()};
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
            && winMousePos.y > m_UI.m_saveBtn.getSize().y * 1.5f
            && winMousePos.x < m_window.getSize().x
            - m_UI.m_addNoteBtn.getSize().x * 1.5f && winMousePos.x > 0.0f
            && winMousePos.y < m_window.getSize().y) {
            
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
    m_UI.render(m_window);
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
    float navBarSize = m_UI.m_saveBtn.getSize().y * 1.5f;
    float vertBarSize = m_UI.m_addNoteBtn.getSize().x * 1.5f;

    sf::Vector2f vpcenter = m_viewport.getCenter();
    m_viewport = sf::View(sf::FloatRect(0.f, 0.f,
        m_window.getSize().x - vertBarSize,
        m_window.getSize().y - navBarSize));
    m_viewport.setCenter(vpcenter);

    m_viewport.setViewport(sf::FloatRect(0.0f,
        1.0f - (m_window.getSize().y - navBarSize)
        / m_window.getSize().y,
        (m_window.getSize().x - vertBarSize)
        / m_window.getSize().x,
        (m_window.getSize().y - navBarSize)
        / m_window.getSize().y));
    
    m_normalView = sf::View(sf::FloatRect(0.f, 0.f,
        m_window.getSize().x, m_window.getSize().y));
    
    m_vpzoom = 1.0f;

    m_UI.recalculate(m_window);
}

void App::processMouseInput(sf::Event& event) {
    sf::Vector2i winMousePos{sf::Mouse::getPosition(m_window)};
    sf::Vector2f vpMousePos{m_window.mapPixelToCoords(winMousePos, m_viewport)};

    if(winMousePos.y > m_UI.m_saveBtn.getSize().y * 1.5f
        && winMousePos.x < m_window.getSize().x
        - m_UI.m_addNoteBtn.getSize().x * 1.5f) {
        
        m_project.setActiveLines(vpMousePos);
        m_lastAL = m_project.getActiveLines();
    }

    if(event.mouseButton.button == sf::Mouse::Left) {
        if(m_UI.m_addNoteBtn.isPointed(m_window.mapPixelToCoords(winMousePos))) {
            m_project.addNote();
            m_lastAL = m_project.getActiveLines();
            m_project.moveActiveLines(sf::Vector2i(0, 1));
        } else if(m_UI.m_deleteBtn.isPointed(m_window.mapPixelToCoords(
            winMousePos))) {

            m_project.deleteNote();
        } else if(m_UI.m_saveBtn.isPointed(m_window.mapPixelToCoords(
            winMousePos))) {

            m_project.getName() == std::string{} ? saveAsDialog() : m_project.save();
        } else if(m_UI.m_saveAsBtn.isPointed(m_window.mapPixelToCoords(
            winMousePos))) {

            saveAsDialog();
        } else if(m_UI.m_exportBtn.isPointed(m_window.mapPixelToCoords(
            winMousePos))) {

            exportDialog();
        } else if(m_UI.m_openBtn.isPointed(m_window.mapPixelToCoords(
            winMousePos))) {

            openDialog();
        } else if(m_UI.m_settingsBtn.isPointed(m_window.mapPixelToCoords(
            winMousePos))) {

            Settings::start(m_window);
        }

        for(uint16_t i{}; i < m_UI.m_chBtn.size(); ++i) {
            if(m_UI.m_chBtn.at(i).isPointed(m_window.mapPixelToCoords(
                winMousePos))) {

                sf::Vector2i ALbuf{m_project.getActiveLines()};

                m_project.setActiveLines(m_lastAL);
                m_project.setChord(i);
                m_project.setActiveLines(ALbuf);
            }
        }
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
        processZoom(event);
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
