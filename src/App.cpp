#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadTexture("res/dot.png");

        m_resources.loadFont("res/PlayfairDisplay.ttf");

        m_testText.setFont(m_resources.getFont(0));
        m_testText.setString("totally test text!");
        m_testText.setCharacterSize(25);

        m_testButton = Button("And totally test button", 
            m_resources.getFont(0), 30, sf::Vector2f(270, 25),
            sf::Vector2f(200, 300), sf::Color::Black, sf::Color::White,
            sf::Color::Green, sf::Color::Red);

        m_imageBtnTest = Button("", m_resources.getFont(0), 1,
            sf::Vector2f(30, 30), sf::Vector2f(500, 500));
        m_imageBtnTest.enableTexture(true, m_resources.getTexture(0));
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

            if(m_testButton.isClicked(mousePos)) {
                m_window.close();
            }
            if(m_imageBtnTest.isClicked(mousePos)) {
                m_window.close();
            }

            m_window.clear(sf::Color(20, 20, 30));

            m_window.draw(m_testText);
            m_testButton.render(m_window);
            m_imageBtnTest.render(m_window);

            m_window.display();
        }

        return 0;
    }
}