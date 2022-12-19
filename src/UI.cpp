#include "UI.hpp"

namespace cmt {
    UI::UI() { }

    void UI::init(ResourceManager& resources) {
        initHNavBar(resources);
        initVNavBar(resources);
    }

    void UI::render(sf::RenderWindow& target) {
        // horizontal navbar
        m_saveBtn.render(target);
        m_exportBtn.render(target);
        m_openBtn.render(target);
        m_settingsBtn.render(target);

        // vertical navbar
        m_editBtn.render(target);
        m_deleteBtn.render(target);
        for(auto btn : m_chBtn) {
            btn.render(target);
        }
    }

    void UI::recalculate(sf::RenderWindow& window) {
        // vertical buttons positions
        float xVerBtnsPos =
            static_cast<float>(window.getSize().x)
            - m_editBtn.getBounds().width - 10;

        m_editBtn.setPos(sf::Vector2f(xVerBtnsPos, 40.0f));

        m_deleteBtn.setPos(sf::Vector2f(xVerBtnsPos, m_editBtn.getPos().y
            + m_deleteBtn.getBounds().height + 15.0f));

        m_chBtn.at(0).setPos(sf::Vector2f(xVerBtnsPos,
            m_deleteBtn.getPos().y
            + m_deleteBtn.getBounds().height + 15.0f));

        for(uint16_t c{0}; c < m_chBtn.size() - 1; ++c) {
            m_chBtn.at(c + 1).setPos(sf::Vector2f(xVerBtnsPos,
                10.0f + m_chBtn.at(c).getPos().y
                + m_chBtn.at(c).getBounds().height));
        }
    }

    void UI::initHNavBar(ResourceManager& resources) {
        m_saveBtn = TextButton(resources.getFont(0), "Save", 25,
            sf::Vector2f(5.0f, 5.0f));

        m_exportBtn = TextButton(resources.getFont(0), "Export", 25,
            sf::Vector2f(m_saveBtn.getPos().x
            + m_saveBtn.getBounds().width + 5.0f, 5.0f));

        m_openBtn = TextButton(resources.getFont(0), "Open", 25,
            sf::Vector2f(m_exportBtn.getPos().x
            + m_exportBtn.getBounds().width + 5.0f, 5.0f));

        m_settingsBtn = TextButton(resources.getFont(0), "Settings", 25,
            sf::Vector2f(m_openBtn.getPos().x
            + m_openBtn.getBounds().width + 5.0f, 5.0f));
    }

    void UI::initVNavBar(ResourceManager& resources) {
        m_editBtn = ImageButton(resources.getTexture(0),
            sf::Vector2f(40.0f, 40.0f), 4);

        for(uint16_t c{0}; c < m_chBtn.size() - 1; ++c) {
            m_chBtn.at(c) = TextButton(resources.getFont(0),
                std::to_string(c + 1), 40);
        }
        m_chBtn.back() = TextButton(resources.getFont(0),
            std::to_string(0), 40);

        m_deleteBtn = ImageButton(resources.getTexture(1),
            sf::Vector2f(40.0f, 40.0f), 4);
    }
}