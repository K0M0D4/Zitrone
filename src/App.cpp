#include "App.hpp"

namespace cmt {
    App::App() {
        m_window.create(sf::VideoMode(1280, 720), "Zitrone");
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

        for(uint16_t c{0}; c < 6; ++c) {
            m_chBtn.at(c) = TextButton(m_resources.getFont(0),
                std::to_string(c + 1), 40);
        }

        m_moveButton = ImageButton(m_resources.getTexture(1),
            sf::Vector2f(40.0f, 40.0f), 4);

        m_workspace.setOutlineThickness(5);
        m_workspace.setFillColor(sf::Color::Transparent);
        m_workspace.setOutlineColor(sf::Color::White);

        /*m_grid.emplace_back(DashLine{sf::Vector2f{100.0f, 0.0f},
            sf::Vector2f{100.0f, 29.7f * m_dpcm},
            20.0f});*/

        m_testLine = DashLine{sf::Vector2f{100.0f, 0.0f},
            sf::Vector2f{100.0f, 29.7f * m_dpcm},
            20.0f, sf::Color::Red};
    }

    int32_t App::start() {
        while(m_window.isOpen()) {
            update();
            render();
            m_window.display();
        }

        return 0;
    }

    void App::update() {
        sf::Event event;
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                m_window.close();

            if(event.type == sf::Event::Resized) {
                // views stuff
                float navBarSize = m_saveBtn.getSize().y * 1.5f;
                float vertBarSize = m_noteBtn.getSize().x * 1.5f;

                sf::Vector2f vpcenter = m_viewport.getCenter();
                m_viewport = sf::View(sf::FloatRect(0.f, 0.f,
                    event.size.width - vertBarSize,
                    event.size.height - navBarSize));
                m_viewport.setCenter(vpcenter);

                m_viewport.setViewport(sf::FloatRect(0.0f,
                    1.0f - (m_window.getSize().y - navBarSize)
                    / m_window.getSize().y,
                    (m_window.getSize().x - vertBarSize)
                    / m_window.getSize().x,
                    (m_window.getSize().y - navBarSize)
                    / m_window.getSize().y));
                
                m_normalView = sf::View(sf::FloatRect(0.f, 0.f,
                    event.size.width, event.size.height));

                // vertical buttons positions
                float xVerBtnsPos =
                    static_cast<float>(m_window.getSize().x)
                    - m_noteBtn.getBounds().width - 10;

                m_noteBtn.setPos(sf::Vector2f(xVerBtnsPos, 40.0f));

                m_chBtn.at(0).setPos(sf::Vector2f(xVerBtnsPos,
                    m_noteBtn.getPos().y
                    + m_noteBtn.getBounds().height + 15.0f));

                for(uint16_t c{0}; c < 5; ++c) {
                    m_chBtn.at(c + 1).setPos(sf::Vector2f(xVerBtnsPos,
                        10.0f + m_chBtn.at(c).getPos().y
                        + m_chBtn.at(c).getBounds().height));
                }

                m_moveButton.setPos(sf::Vector2f(xVerBtnsPos, 15.0f
                    + m_chBtn.back().getPos().y
                    + m_chBtn.back().getBounds().height));
            }
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            m_viewport.zoom(0.99f);
            m_vpzoom *= 0.99f;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            m_viewport.zoom(1.01f);
            m_vpzoom *= 1.01f;
        }

        sf::Vector2f mousePos{m_window.mapPixelToCoords(
                sf::Mouse::getPosition(m_window))};

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

        m_viewport.move(static_cast<float>(-m_deltaMousePos.x) * m_vpzoom,
            static_cast<float>(-m_deltaMousePos.y) * m_vpzoom);
    }

    void App::render() {
        m_window.clear(sf::Color(20, 20, 30));

            // viewport
            m_window.setView(m_viewport);
            m_window.draw(m_workspace);
            /*for(uint32_t i{0}; i < m_grid.size(); ++i) {
                m_grid.at(i).render(m_window);
            }
            m_grid.at(0).render(m_window);*/
            m_testLine.render(m_window);

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
    }
}