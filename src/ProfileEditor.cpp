#include "ProfileEditor.hpp"

ProfileEditor::ProfileEditor() {
    
}

void ProfileEditor::start(cmt::ResourceManager& resources,
    std::vector<std::string>& languageData) {

    m_resources = &resources;
    m_languageData = &languageData;

    std::string windowName{"Zitrone - " + m_languageData->at(11)};
    windowName.erase(windowName.size() - 1, 1);

    m_window.create(sf::VideoMode(720, 720), windowName);
    m_GUI.setTarget(m_window);
    
    while(m_window.isOpen()) {
        update();
        render();
        m_window.display();
    }
}

void ProfileEditor::update() {
    sf::Event event{};
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void ProfileEditor::render() {
    m_window.clear(m_resources->getTheme(0).getBgColor());
}
