#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadTexture("res/dot.png");
        m_resources.loadTexture("res/move.png");
        m_resources.loadTexture("res/background.png");
        m_resources.getTexture(2).setRepeated(true);

        m_resources.loadFont("res/PlayfairDisplay.ttf");

        // viewport
        m_background.setTexture(m_resources.getTexture(2));
        m_background.setTextureRect(sf::IntRect(0, 0, 4096, 4096));

        // horizontal navbar
        m_saveBtn = TextButton(m_resources.getFont(0), "Save", 25,
            sf::Vector2f(5.0f, 5.0f));

        m_exportBtn = TextButton(m_resources.getFont(0), "Export", 25,
            sf::Vector2f(m_saveBtn.getPos().x
            + m_saveBtn.getBounds().width + 5.0f, 5.0f));

        m_openBtn = TextButton(m_resources.getFont(0), "Open", 25,
            sf::Vector2f(m_exportBtn.getPos().x
            + m_exportBtn.getBounds().width + 5.0f, 5.0f));

        m_settingsBtn = TextButton(m_resources.getFont(0), "Settings", 25,
            sf::Vector2f(m_openBtn.getPos().x
            + m_openBtn.getBounds().width + 5.0f, 5.0f));

        // vertical buttons
        m_noteBtn = ImageButton(m_resources.getTexture(0),
            sf::Vector2f(40.0f, 40.0f), 4);

        float xVerBtnsPos = static_cast<float>(m_window.getSize().x)
            - m_noteBtn.getBounds().width - 10;

        m_noteBtn.setPos(sf::Vector2f(xVerBtnsPos, 40.0f));

        // chord buttons
        for(uint16_t c{0}; c < 6; ++c) {
            m_chBtn.at(c) = TextButton(m_resources.getFont(0),
                std::to_string(c + 1), 40);
        }
        m_chBtn.at(0).setPos(sf::Vector2f(xVerBtnsPos,
            m_noteBtn.getPos().y + m_noteBtn.getBounds().height + 15.0f));
        for(uint16_t c{0}; c < 5; ++c) {
            m_chBtn.at(c + 1).setPos(sf::Vector2f(xVerBtnsPos, 10.0f
                + m_chBtn.at(c).getPos().y
                + m_chBtn.at(c).getBounds().height));
        }

        // move button
        m_moveButton = ImageButton(m_resources.getTexture(1),
            sf::Vector2f(40.0f, 40.0f), 4);

        m_moveButton.setPos(sf::Vector2f(xVerBtnsPos, 15.0f +
            m_chBtn.back().getPos().y + m_chBtn.back().getBounds().height));
    }

    int32_t App::start() {
        while(m_window.isOpen()) {
            // input
            sf::Event event;
            while(m_window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    m_window.close();

                if (event.type == sf::Event::Resized)
                {
                    sf::FloatRect visibleArea(0.f, 0.f,
                        event.size.width, event.size.height);
                    m_window.setView(sf::View(visibleArea));
                }

                if (event.type == sf::Event::Resized) {
                    float navBarSize = m_saveBtn.getSize().y * 1.5f;
                    float vertBarSize = m_moveButton.getSize().x * 1.5f;

                    m_viewport = sf::View(sf::FloatRect(0.f, 0.f,
                        event.size.width - vertBarSize,
                        event.size.height - navBarSize));

                    m_viewport.setViewport(sf::FloatRect(0.0f,
                        1.0f - (m_window.getSize().y - navBarSize)
                        / m_window.getSize().y,
                        (m_window.getSize().x - vertBarSize)
                        / m_window.getSize().x,
                        (m_window.getSize().y - navBarSize)
                        / m_window.getSize().y));

                    m_normalView = sf::View(sf::FloatRect(0.f, 0.f,
                        event.size.width, event.size.height));

                    
                }
            }

            sf::Vector2f mousePos{};
            mousePos.x = sf::Mouse::getPosition(m_window).x;
            mousePos.y = sf::Mouse::getPosition(m_window).y;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i realPos = sf::Mouse::getPosition(m_window);
                if(m_wasMousePressed) {
                    m_deltaMousePos = realPos - m_prevMousePos;
                }
                m_prevMousePos = realPos;
                m_wasMousePressed = true;
            } else {
                m_wasMousePressed = false;
                m_prevMousePos = sf::Vector2i{};
                m_deltaMousePos = sf::Vector2i{};
            }

            m_viewport.move(static_cast<float>(-m_deltaMousePos.x),
                static_cast<float>(-m_deltaMousePos.y));

            // rendering
            m_window.clear(sf::Color(20, 20, 30));

            m_window.setView(m_viewport);
            m_window.draw(m_background);

            // horizontal navbar
            m_window.setView(m_normalView);
            m_saveBtn.render(m_window);
            m_exportBtn.render(m_window);
            m_openBtn.render(m_window);
            m_settingsBtn.render(m_window);

            // vertical buttons
            m_noteBtn.render(m_window);
            for(auto btn : m_chBtn) {
                btn.render(m_window);
            }
            m_moveButton.render(m_window);

            m_window.display();
        }

        return 0;
    }
}