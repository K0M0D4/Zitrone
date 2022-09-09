#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone",
            sf::Style::Titlebar | sf::Style::Close);
        m_window.setVerticalSyncEnabled(true);

        m_resources.loadTexture("res/dot.png");
        m_resources.loadTexture("res/move.png");

        m_resources.loadFont("res/PlayfairDisplay.ttf");

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
            sf::Event event;
            while(m_window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    m_window.close();
            }

            sf::Vector2f mousePos{};
            mousePos.x = sf::Mouse::getPosition(m_window).x;
            mousePos.y = sf::Mouse::getPosition(m_window).y;

            m_window.clear(sf::Color(20, 20, 30));

            // horizontal navbar
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