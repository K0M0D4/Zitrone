#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone",
            sf::Style::Titlebar | sf::Style::Close);
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadTexture("res/dot.png");

        m_resources.loadFont("res/PlayfairDisplay.ttf");

        m_testImageBtn = ImageButton(m_resources.getTexture(0),
            sf::Vector2f(60.0f, 60.0f), 5, sf::Vector2f(5.0f, 5.0f));

        m_testImageBtn.enable = false;

        m_plusBtn = TextButton(m_resources.getFont(0), "+", 27);

        m_minusBtn = TextButton(m_resources.getFont(0), "-", 27);

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

            if(m_plusBtn.isPressed(mousePos)) {
                m_testImageBtn.setSize(m_testImageBtn.getSize()
                    + sf::Vector2f(5.0f, 5.0f));
            }

            if(m_minusBtn.isPressed(mousePos)) {
                m_testImageBtn.setSize(m_testImageBtn.getSize()
                    - sf::Vector2f(5.0f, 5.0f));
            }

            m_plusBtn.setPos(sf::Vector2f(m_testImageBtn.getPos().x
                + m_testImageBtn.getBounds().width + 5.0f,
                m_testImageBtn.getPos().y));

            m_minusBtn.setPos(sf::Vector2f(m_plusBtn.getPos().x,
                m_plusBtn.getPos().y + m_plusBtn.getBounds().height + 5.0f));

            m_window.clear(sf::Color(20, 20, 30));

            m_testImageBtn.render(m_window);

            m_plusBtn.render(m_window);
            m_minusBtn.render(m_window);

            m_window.display();
        }

        return 0;
    }
}