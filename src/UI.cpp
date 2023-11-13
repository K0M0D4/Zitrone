#include "UI.hpp"

#include <fstream>

UI::UI() {}

void UI::init(cmt::ResourceManager& resources, const std::string& langFilepath) {
    m_btnTextColor = resources.getTheme(0).getColor(2);
    m_btnNormalColor = resources.getTheme(0).getColor(1);
    m_btnPointColor = sf::Color{resources.getTheme(0).getColor(1).r,
        resources.getTheme(0).getColor(1).g, resources.getTheme(0).getColor(1).b, 160};
    m_btnPressColor = sf::Color{resources.getTheme(0).getColor(1).r,
        resources.getTheme(0).getColor(1).g, resources.getTheme(0).getColor(1).b, 90};

    loadLanguage(langFilepath);

    initNavBars(resources);
}

void UI::render(sf::RenderWindow& target) {
    // horizontal navbar
    // m_saveBtn.render(target);
    // m_saveAsBtn.render(target);
    // m_exportBtn.render(target);
    // m_openBtn.render(target);
    // m_settingsBtn.render(target);

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

void UI::initNavBars(cmt::ResourceManager& resources) {
    // horizontal
    m_saveBtn = createTextBtn(resources, m_textData.at(0), sf::Vector2f{5.0f, 55.0f}) ;
    m_saveAsBtn = createTextBtn(resources, m_textData.at(1),
        sf::Vector2f(m_saveBtn.getPos().x + m_saveBtn.getBounds().width + 5.0f, 55.0f));
    m_exportBtn = createTextBtn(resources, m_textData.at(2),
        sf::Vector2f(m_saveAsBtn.getPos().x + m_saveAsBtn.getBounds().width + 5.0f, 55.0f));
    m_openBtn = createTextBtn(resources, m_textData.at(3),
        sf::Vector2f(m_exportBtn.getPos().x + m_exportBtn.getBounds().width
        + 5.0f, 55.0f));
    m_settingsBtn = createTextBtn(resources, m_textData.at(4),
        sf::Vector2f(m_openBtn.getPos().x + m_openBtn.getBounds().width + 5.0f, 55.0f));

    // vertical
    m_addNoteBtn = createImageBtn(resources, 0);
    m_deleteBtn = createImageBtn(resources, 1);

    for(uint16_t c{}; c < m_chBtn.size(); ++c) {
        m_chBtn.at(c) = createTextBtn(resources, std::to_string(c), sf::Vector2f{});
        m_chBtn.at(c).setSize(40);
    }
}

cmt::TextButton UI::createTextBtn(cmt::ResourceManager& resources, const std::string& text,
    sf::Vector2f pos) {

    return cmt::TextButton{resources.getFont(0), text, 25, pos, m_padding,
        m_btnTextColor, m_btnNormalColor, m_btnPointColor, m_btnPressColor};
}

cmt::ImageButton UI::createImageBtn(cmt::ResourceManager& resources, uint16_t textureID) {
    return cmt::ImageButton{resources.getTexture(textureID),
        sf::Vector2f(40.0f, 40.0f), m_padding, sf::Vector2f{},
        m_btnNormalColor, m_btnPointColor, m_btnPressColor};
}

void UI::loadLanguage(const std::string& filepath) {
    std::ifstream file("res/languages/" + filepath + ".txt");
    if(!file.good())
        throw std::runtime_error("Error: Can't read language: "
            + filepath + '\n');

    for(uint16_t i{}; i < m_textData.size(); ++i) {
        getline(file, m_textData.at(i));
    }
}
