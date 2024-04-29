#include "ProfileEditor.hpp"

ProfileEditor::ProfileEditor() {
    
}

void ProfileEditor::start(cmt::ResourceManager& resources,
    std::vector<std::string>& languageData) {

    m_resources = &resources;
    m_languageData = &languageData;

    std::string windowName{"Zitrone - " + m_languageData->at(11)};

    m_window.create(sf::VideoMode(720, 720), windowName);
    m_GUI.setTarget(m_window);

    initButtons();
    
    while(m_window.isOpen()) {
        update();
        render();
        m_window.display();
    }
}

void ProfileEditor::update() {
    sf::Event event{};
    while(m_window.pollEvent(event)) {
        m_GUI.handleEvent(event);

        if(event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void ProfileEditor::render() {
    m_window.clear(m_resources->getTheme(0).getBgColor());

    m_GUI.draw();
}

void ProfileEditor::initButtons() {
    setupBtnsNames();
    setupBtnsLook();
    setupBtnsBehaviour();
}

void ProfileEditor::setupBtnsNames() {
    m_pageWidthLabel = tgui::Button::create(m_languageData->at(12));
    m_pageHeightLabel = tgui::Button::create(m_languageData->at(13));
    m_cutLineXLabel = tgui::Button::create(m_languageData->at(14));
    m_cutLineYLabel = tgui::Button::create(m_languageData->at(15));
    m_verticalBreakLabel = tgui::Button::create(m_languageData->at(16));
    m_horizontalBreakLabel = tgui::Button::create(m_languageData->at(17));
    m_firstNoteOffsetLabel = tgui::Button::create(m_languageData->at(18));

    m_pageWidthInput = tgui::EditBox::create();
    m_pageHeightInput = tgui::EditBox::create();
    m_cutLineXInput = tgui::EditBox::create();
    m_cutLineYInput = tgui::EditBox::create();
    m_verticalBreakInput = tgui::EditBox::create();
    m_horizontalBreakInput = tgui::EditBox::create();
    m_firstNoteOffsetInput = tgui::EditBox::create();
}

void ProfileEditor::setupBtnsLook() {
    // Labels
    m_pageWidthLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_pageWidthLabel->setPosition(30, 30);
    m_pageWidthLabel->setTextSize(17);

    m_GUI.add(m_pageWidthLabel);

    m_pageHeightLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_pageHeightLabel->setPosition("50%", {bindTop(m_pageWidthLabel)});
    m_pageHeightLabel->setTextSize(17);

    m_GUI.add(m_pageHeightLabel);

    m_cutLineXLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_cutLineXLabel->setPosition({bindLeft(m_pageWidthLabel)}, {bindBottom(m_pageWidthLabel) + 20});
    m_cutLineXLabel->setTextSize(17);

    m_GUI.add(m_cutLineXLabel);

    m_cutLineYLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_cutLineYLabel->setPosition("50%", {bindTop(m_cutLineXLabel)});
    m_cutLineYLabel->setTextSize(17);

    m_GUI.add(m_cutLineYLabel);

    m_verticalBreakLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_verticalBreakLabel->setPosition({bindLeft(m_pageWidthLabel)}, {bindBottom(m_cutLineXLabel) + 20});
    m_verticalBreakLabel->setTextSize(17);

    m_GUI.add(m_verticalBreakLabel);

    m_horizontalBreakLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_horizontalBreakLabel->setPosition("50%", {bindTop(m_verticalBreakLabel)});
    m_horizontalBreakLabel->setTextSize(17);

    m_GUI.add(m_horizontalBreakLabel);

    m_firstNoteOffsetLabel->setRenderer(tgui::Theme::getDefault()->getRenderer("Label"));
    m_firstNoteOffsetLabel->setPosition({bindLeft(m_pageWidthLabel)}, {bindBottom(m_verticalBreakLabel) + 20});
    m_firstNoteOffsetLabel->setTextSize(17);

    m_GUI.add(m_firstNoteOffsetLabel);

    // Input boxes
    m_pageWidthInput->setSize(100, 27);
    m_pageWidthInput->setTextSize(17);
    m_pageWidthInput->setPosition("50% - 115", {bindTop(m_pageWidthLabel)});
    m_pageWidthInput->setText("1.0f");

    m_GUI.add(m_pageWidthInput);

    m_pageHeightInput->setSize(100, 27);
    m_pageHeightInput->setTextSize(17);
    m_pageHeightInput->setPosition("100% - 115", {bindTop(m_pageHeightLabel)});
    m_pageHeightInput->setText("2.0f");

    m_GUI.add(m_pageHeightInput);

    m_cutLineXInput->setSize(100, 27);
    m_cutLineXInput->setTextSize(17);
    m_cutLineXInput->setPosition("50% - 115", {bindTop(m_cutLineXLabel)});
    m_cutLineXInput->setText("1.0f");

    m_GUI.add(m_cutLineXInput);

    m_cutLineYInput->setSize(100, 27);
    m_cutLineYInput->setTextSize(17);
    m_cutLineYInput->setPosition("100% - 115", {bindTop(m_cutLineYLabel)});
    m_cutLineYInput->setText("2.0f");

    m_GUI.add(m_cutLineYInput);

    m_verticalBreakInput->setSize(100, 27);
    m_verticalBreakInput->setTextSize(17);
    m_verticalBreakInput->setPosition("50% - 115", {bindTop(m_verticalBreakLabel)});
    m_verticalBreakInput->setText("1.0f");

    m_GUI.add(m_verticalBreakInput);

    m_horizontalBreakInput->setSize(100, 27);
    m_horizontalBreakInput->setTextSize(17);
    m_horizontalBreakInput->setPosition("100% - 115", {bindTop(m_horizontalBreakLabel)});
    m_horizontalBreakInput->setText("2.0f");

    m_GUI.add(m_horizontalBreakInput);

    m_firstNoteOffsetInput->setSize(100, 27);
    m_firstNoteOffsetInput->setTextSize(17);
    m_firstNoteOffsetInput->setPosition("50% - 115", {bindTop(m_firstNoteOffsetLabel)});
    m_firstNoteOffsetInput->setText("1.0f");

    m_GUI.add(m_firstNoteOffsetInput);
}

void ProfileEditor::setupBtnsBehaviour() {

}

