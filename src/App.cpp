#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadTexture("res/dot.png");

        m_resources.loadFont("res/PlayfairDisplay.ttf");

        m_newBtn = Button("New", 
            m_resources.getFont(0), 25, sf::Vector2f(100, 25),
            sf::Vector2f(5, 5));

        m_saveBtn = Button("Save", 
            m_resources.getFont(0), 25, sf::Vector2f(120, 25),
            sf::Vector2f(110, 5));

        m_exportBtn = Button("Export", 
            m_resources.getFont(0), 25, sf::Vector2f(150, 25),
            sf::Vector2f(220, 5));

        m_loadBtn = Button("Load", 
            m_resources.getFont(0), 25, sf::Vector2f(100, 25),
            sf::Vector2f(330, 5));
        
        m_settingsBtn = Button("Settings", 
            m_resources.getFont(0), 25, sf::Vector2f(100, 25),
            sf::Vector2f(440, 5));


        m_imageBtnTest = Button("", m_resources.getFont(0), 1,
            sf::Vector2f(30, 30), sf::Vector2f(500, 500));
        m_imageBtnTest.enableTexture(m_resources.getTexture(0));
    }

    int32_t App::start() {
        while(m_window.isOpen()) {
            sf::Event event;
            while(m_window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    m_window.close();
            }

            sf::Vector2f mousePos{};
            mousePos.x = sf::Mouse::getPosition(m_window).x;
            mousePos.y = sf::Mouse::getPosition(m_window).y;

            if(m_imageBtnTest.isClicked(mousePos)) {
                m_window.close();
            }

            m_window.clear(sf::Color(20, 20, 30));

            m_newBtn.render(m_window);
            m_saveBtn.render(m_window);
            m_exportBtn.render(m_window);
            m_loadBtn.render(m_window);
            m_settingsBtn.render(m_window);

            m_imageBtnTest.render(m_window);

            m_window.display();
        }

        return 0;
    }
}