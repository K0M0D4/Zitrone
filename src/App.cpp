#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadTexture("res/dot.png");
        m_resources.loadTexture("res/move.png");

        m_resources.loadFont("res/PlayfairDisplay.ttf");

        m_UI.init(m_resources);
    }

    int32_t App::start() {
        while(m_window.isOpen()) {
            update();
            render();
            m_window.display();
        }

        return 0;
    }

    void App::update() {
        sf::Event event;
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                m_window.close();

            if(event.type == sf::Event::Resized) {
                // viewport stuff
                float navBarSize = m_UI.m_saveBtn.getSize().y * 1.5f;
                float vertBarSize = m_UI.m_noteBtn.getSize().x * 1.5f;

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

                m_UI.recalculate(m_window);
            }

            if(event.type == sf::Event::KeyPressed) {
                m_project.moveActiveLines(event.key.code);

                if(event.key.code == sf::Keyboard::Space) {
                    m_project.addNote();
                }
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos{sf::Mouse::getPosition(m_window)};

                m_project.setActiveLines(m_window.mapPixelToCoords(
                        mousePos, m_viewport));
            }
        }
        
        if(m_window.hasFocus()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
                m_viewport.zoom(0.99f);
                m_vpzoom *= 0.99f;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
                m_viewport.zoom(1.01f);
                m_vpzoom *= 1.01f;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                if(m_wasMousePressed) {
                    m_deltaMousePos = mousePos - m_prevMousePos;
                }
                m_prevMousePos = mousePos;
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
        m_window.clear(sf::Color(20, 20, 30));

            // viewport
            m_window.setView(m_viewport);
            m_project.render(m_window);

            // UI
            m_window.setView(m_normalView);
            m_UI.render(m_window);
    }
}