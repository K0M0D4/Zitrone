#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadFont("res/PlayfairDisplay.ttf");

        m_testText.setFont(m_resources.getFont(0));
        m_testText.setString("totally test text!");
        m_testText.setCharacterSize(20);
        
    }

    int32_t App::start() {
        while(m_window.isOpen()) {
            sf::Event event;
            while(m_window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_window.clear(sf::Color(20, 20, 30));

            m_window.draw(m_testText);

            m_window.display();
        }

        return 0;
    }
}