#include "ProfileEditor.hpp"

ProfileEditor::ProfileEditor() {
    
}

void ProfileEditor::start() {
    m_window.create(sf::VideoMode(720, 720), "Zitrone - profile editor");
    m_GUI.setTarget(m_window);

    while(m_window.isOpen()) {
        sf::Event event{};
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        m_window.clear(sf::Color::Blue);

        m_window.display();
    }
}
