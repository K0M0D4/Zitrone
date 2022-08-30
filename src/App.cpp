#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
    }

    int32_t App::start() {
        while(m_window.isOpen()) {
            sf::Event event;
            while(m_window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_window.clear(sf::Color(20, 20, 30));

            m_window.display();
        }

        return 0;
    }
}