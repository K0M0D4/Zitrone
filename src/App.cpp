#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadTexture("res/dot.png");

        m_resources.loadFont("res/PlayfairDisplay.ttf");

        m_testBtn = Button(sf::Vector2f(100.0f, 20.0f),
            sf::Vector2f(5.0f, 5.0f));

        m_testImageBtn = ImageButton(m_resources.getTexture(0),
            sf::Vector2f(60.0f, 60.0f), 5,
            sf::Vector2f(m_testBtn.getPos().x
            + m_testBtn.getBounds().width + 5.0f, 5.0f));

        m_testTextBtn = TextButton(m_resources.getFont(0),
            "Total test button!", 30,
            sf::Vector2f(175.0f, 5.0f));
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

            if(m_testTextBtn.isPressed(mousePos)) {
                //m_window.close();
            }

            m_window.clear(sf::Color(20, 20, 30));

            m_testBtn.render(m_window);
            m_testImageBtn.render(m_window);
            m_testTextBtn.render(m_window);

            m_window.display();
        }

        return 0;
    }
}