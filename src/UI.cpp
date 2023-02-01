#include "UI.hpp"

namespace cmt {
    UI::UI() {}

    UI::UI(ResourceManager& resources) {
        m_btnTextColor = resources.getTheme(0).getColor(2);
        m_btnNormalColor = resources.getTheme(0).getColor(1);
        m_btnPointColor = sf::Color{resources.getTheme(0).getColor(1).r,
            resources.getTheme(0).getColor(1).g, resources.getTheme(0).getColor(1).b, 160};
        m_btnPressColor = sf::Color{resources.getTheme(0).getColor(1).r,
            resources.getTheme(0).getColor(1).g, resources.getTheme(0).getColor(1).b, 90};

        initNavBars(resources);
    }

    void UI::render(sf::RenderWindow& target) {
        // horizontal navbar
        m_saveBtn.render(target);
        m_saveAsBtn.render(target);
        m_exportBtn.render(target);
        m_openBtn.render(target);
        m_settingsBtn.render(target);

        // vertical navbar
        m_addNoteBtn.render(target);
        m_deleteBtn.render(target);
        for(auto btn : m_chBtn) {
            btn.render(target);
        }
    }

    void UI::recalculate(sf::RenderWindow& window) {
        // vertical buttons positions
        float xVerBtnsPos =
            static_cast<float>(window.getSize().x)
            - m_addNoteBtn.getBounds().width - 10;

        m_addNoteBtn.setPos(sf::Vector2f(xVerBtnsPos, 40.0f));

        m_deleteBtn.setPos(sf::Vector2f(xVerBtnsPos, m_addNoteBtn.getPos().y
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

    void UI::initNavBars(ResourceManager& resources) {
        // horizontal
        m_saveBtn = createTextBtn(resources, "Save", sf::Vector2f{5.0f, 5.0f}) ;
        m_saveAsBtn = createTextBtn(resources, "Save as",
            sf::Vector2f(m_saveBtn.getPos().x + m_saveBtn.getBounds().width + 5.0f, 5.0f));
        m_exportBtn = createTextBtn(resources, "Export",
            sf::Vector2f(m_saveAsBtn.getPos().x + m_saveAsBtn.getBounds().width + 5.0f, 5.0f));
        m_openBtn = createTextBtn(resources, "Open",
            sf::Vector2f(m_exportBtn.getPos().x + m_exportBtn.getBounds().width
            + 5.0f, 5.0f));
        m_settingsBtn = createTextBtn(resources, "Settings",
            sf::Vector2f(m_openBtn.getPos().x + m_openBtn.getBounds().width + 5.0f, 5.0f));
    
        // vertical
        m_addNoteBtn = createImageBtn(resources, 0);
        m_deleteBtn = createImageBtn(resources, 1);

        for(uint16_t c{}; c < m_chBtn.size(); ++c) {
            m_chBtn.at(c) = createTextBtn(resources, std::to_string(c), sf::Vector2f{});
            m_chBtn.at(c).setSize(40);
        }
    }

    TextButton UI::createTextBtn(ResourceManager& resources, const std::string& text,
        sf::Vector2f pos) {

        return TextButton{resources.getFont(0), text, 25, pos, m_padding,
            m_btnTextColor, m_btnNormalColor, m_btnPointColor, m_btnPressColor};
    }

    ImageButton UI::createImageBtn(ResourceManager& resources, uint16_t textureID) {
        return ImageButton{resources.getTexture(textureID),
            sf::Vector2f(40.0f, 40.0f), m_padding, sf::Vector2f{},
            m_btnNormalColor, m_btnPointColor, m_btnPressColor};
    }
}