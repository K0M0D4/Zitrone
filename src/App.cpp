#include "App.hpp"

#include <nfd.h>

#include <fstream>

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
        m_window.setVerticalSyncEnabled(true);
        
        m_resources.loadTexture("res/edit.png");
        m_resources.loadTexture("res/delete.png");
        
        m_resources.loadFont("res/PlayfairDisplay.ttf");

        loadConfig();
        
        m_UI = UI{m_resources, m_lang};
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
        sf::Vector2f vpMousePos{m_window.mapPixelToCoords(winMousePos, m_viewport)};

        sf::Event event;
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
            }

            if(event.type == sf::Event::Resized) {
                // viewport stuff
                float navBarSize = m_UI.m_saveBtn.getSize().y * 1.5f;
                float vertBarSize = m_UI.m_addNoteBtn.getSize().x * 1.5f;

                sf::Vector2f vpcenter = m_viewport.getCenter();
                m_viewport = sf::View(sf::FloatRect(0.f, 0.f,
                    event.size.width - vertBarSize,
                    event.size.height - navBarSize));
                m_viewport.setCenter(vpcenter);

                m_viewport.setViewport(sf::FloatRect(0.0f,
                    1.0f - (m_window.getSize().y - navBarSize)
                    / m_window.getSize().y,
                    (m_window.getSize().x - vertBarSize)
                    / m_window.getSize().x,
                    (m_window.getSize().y - navBarSize)
                    / m_window.getSize().y));
                
                m_normalView = sf::View(sf::FloatRect(0.f, 0.f,
                    event.size.width, event.size.height));
                
                m_vpzoom = 1.0f;

                m_UI.recalculate(m_window);
            }

            if(event.type == sf::Event::MouseWheelScrolled
                && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                
                if(event.mouseWheelScroll.delta > 0 && m_vpzoom > 0.78f) {
                    m_viewport.zoom(0.96f);
                    m_vpzoom *= 0.96f;
                } else {
                    m_viewport.zoom(1.04f);
                    m_vpzoom *= (1.04f);
                }
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                if(winMousePos.y > m_UI.m_saveBtn.getSize().y * 1.5f
                    && winMousePos.x < m_window.getSize().x
                    - m_UI.m_addNoteBtn.getSize().x * 1.5f) {
                    
                    m_project.setActiveLines(vpMousePos);
                }
            }

            if(event.type == sf::Event::KeyPressed) {
                m_project.moveActiveLines(event.key.code);

                switch(event.key.code) {
                case sf::Keyboard::Space:
                    m_project.addNote(); break;
                case sf::Keyboard::Backspace:
                case sf::Keyboard::Delete:
                    m_project.deleteNote(); break;
                }
                    
                if(event.key.code >= sf::Keyboard::Num0
                    && event.key.code <= sf::Keyboard::Num6) {

                    m_project.setChord(event.key.code - 26);
                }
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    && event.key.code == sf::Keyboard::S) {

                    if(m_project.getName() == std::string{}
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                            
                        saveAsDialog();
                    } else {
                        m_project.save();
                    }
                }
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    && event.key.code == sf::Keyboard::O) {

                    openDialog();
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    && event.key.code == sf::Keyboard::E) {

                    exportDialog();
                }
            }
        }

        if(m_window.hasFocus()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) && m_vpzoom > 0.78f) {
                m_viewport.zoom(0.98f);
                m_vpzoom *= 0.98f;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
                m_viewport.zoom(1.02f);
                m_vpzoom *= (1.02f);
            }

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

        if(m_UI.m_addNoteBtn.isPressed(m_window.mapPixelToCoords(winMousePos))) {
            m_project.addNote();
        } else if(m_UI.m_deleteBtn.isPressed(m_window.mapPixelToCoords(
            winMousePos))) {

            m_project.deleteNote();
        } else if(m_UI.m_saveBtn.isPressed(m_window.mapPixelToCoords(
            winMousePos))) {

            if(m_project.getName() == std::string{}) {
                saveAsDialog();
            } else {
                m_project.save();
            }
        } else if(m_UI.m_saveAsBtn.isPressed(m_window.mapPixelToCoords(
            winMousePos))) {

            saveAsDialog();
        } else if(m_UI.m_openBtn.isPressed(m_window.mapPixelToCoords(
            winMousePos))) {

            openDialog();
        } else if(m_UI.m_exportBtn.isPressed(m_window.mapPixelToCoords(
            winMousePos))) {

            exportDialog();
        }

        for(uint16_t i{}; i < m_UI.m_chBtn.size(); ++i) {
            if(m_UI.m_chBtn.at(i).isPressed(m_window.mapPixelToCoords(
                winMousePos))) {

                m_project.setChord(i);
            }
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

        nfdfilteritem_t filterItem[1] {{"Project files", "png"}};

        nfdresult_t result{NFD_SaveDialog(&exportPath, filterItem, 1, NULL, "project.png")};
        
        if(result == NFD_OKAY) {
            m_project.exportProj(exportPath);
            NFD_FreePath(exportPath);
        } else if(result != NFD_CANCEL) {
            throw std::runtime_error("Internal error: "
                + std::string{NFD_GetError()} + '\n');
        }
    }

    void App::loadConfig() {
        std::ifstream config("config");
        if(!config.good())
            throw std::runtime_error("Error: Can't load config file\n");

        sf::Vector2f buffer{};

        std::string line{};

        getline(config, line);
        m_lang = line;
        getline(config, line);
        m_resources.loadTheme("res/themes/" + line);

        getline(config, line);
        buffer.x = std::stof(line);
        getline(config, line);
        buffer.y = std::stof(line);
        m_project = Project{buffer, &m_resources};

        getline(config, line);
        buffer.x = std::stof(line);
        getline(config, line);
        buffer.y = std::stof(line);
        m_project.setCutLine(buffer);

        config.close();
    }
}