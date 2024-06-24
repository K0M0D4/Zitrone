#include "ProfileEditor.hpp"

ProfileEditor::ProfileEditor() {
    
}

void ProfileEditor::start(cmt::ResourceManager& resources,
    std::vector<std::string>& languageData, ProfileManager* profiles,
    const std::string& currentProfile) {

    m_resources = &resources;
    m_languageData = &languageData;
    m_profiles = profiles;
    m_currentProfile = currentProfile;

    m_profiles->switchProfile(m_currentProfile);

    m_GUI.removeAllWidgets();

    std::string windowName{"Zitrone - " + m_languageData->at(11)};

    m_window.create(sf::VideoMode(920, 720), windowName);
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

        m_changeProfileBtn->setSize(250, 33);
        m_changeProfileBtn->setPosition(7, m_window.getSize().y - 40);

        m_currentProfileName->setSize(m_window.getSize().x - 500, 33);
        m_currentProfileName->setPosition(264, m_window.getSize().y - 40);

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

    m_helperImage = tgui::Picture::create();

    m_changeProfileBtn = tgui::Button::create();
    m_currentProfileName = tgui::EditBox::create();
    m_profilesList = tgui::ScrollablePanel::create();

    m_saveBtn = tgui::Button::create();
}

void ProfileEditor::setupBtnsLook() {
    m_profileSwitchers.clear();

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
    std::string valueBuffer{std::to_string(m_profiles->getPageSize().x)};
    m_pageWidthInput->setSize(100, 27);
    m_pageWidthInput->setTextSize(17);
    m_pageWidthInput->setPosition("50% - 115", {bindTop(m_pageWidthLabel)});
    m_pageWidthInput->setText(valueBuffer);

    m_GUI.add(m_pageWidthInput);

    valueBuffer = std::to_string(m_profiles->getPageSize().y);
    m_pageHeightInput->setSize(100, 27);
    m_pageHeightInput->setTextSize(17);
    m_pageHeightInput->setPosition("100% - 115", {bindTop(m_pageHeightLabel)});
    m_pageHeightInput->setText(valueBuffer);

    m_GUI.add(m_pageHeightInput);

    valueBuffer = std::to_string(m_profiles->getCutLine().x);
    m_cutLineXInput->setSize(100, 27);
    m_cutLineXInput->setTextSize(17);
    m_cutLineXInput->setPosition("50% - 115", {bindTop(m_cutLineXLabel)});
    m_cutLineXInput->setText(valueBuffer);

    m_GUI.add(m_cutLineXInput);

    valueBuffer = std::to_string(m_profiles->getCutLine().y);
    m_cutLineYInput->setSize(100, 27);
    m_cutLineYInput->setTextSize(17);
    m_cutLineYInput->setPosition("100% - 115", {bindTop(m_cutLineYLabel)});
    m_cutLineYInput->setText(valueBuffer);

    m_GUI.add(m_cutLineYInput);

    valueBuffer = std::to_string(m_profiles->getBreaks().x);
    m_verticalBreakInput->setSize(100, 27);
    m_verticalBreakInput->setTextSize(17);
    m_verticalBreakInput->setPosition("50% - 115", {bindTop(m_verticalBreakLabel)});
    m_verticalBreakInput->setText(valueBuffer);

    m_GUI.add(m_verticalBreakInput);

    valueBuffer = std::to_string(m_profiles->getBreaks().y);
    m_horizontalBreakInput->setSize(100, 27);
    m_horizontalBreakInput->setTextSize(17);
    m_horizontalBreakInput->setPosition("100% - 115", {bindTop(m_horizontalBreakLabel)});
    m_horizontalBreakInput->setText(valueBuffer);

    m_GUI.add(m_horizontalBreakInput);

    valueBuffer = std::to_string(m_profiles->getFirstNoteOffset());
    m_firstNoteOffsetInput->setSize(100, 27);
    m_firstNoteOffsetInput->setTextSize(17);
    m_firstNoteOffsetInput->setPosition("50% - 115", {bindTop(m_firstNoteOffsetLabel)});
    m_firstNoteOffsetInput->setText(valueBuffer);

    m_GUI.add(m_firstNoteOffsetInput);

    m_helperImage->getRenderer()->setTexture(m_resources->getTexture(13));
    m_helperImage->setSize(400, 200);
    m_helperImage->setPosition("50% - 200", {bindBottom(m_firstNoteOffsetInput) + 100});

    m_GUI.add(m_helperImage);

    m_changeProfileBtn->setText("Change profile");
    m_changeProfileBtn->setTextSize(17);
    m_GUI.add(m_changeProfileBtn);

    m_currentProfileName->setText(m_currentProfile);
    m_currentProfileName->setTextSize(17);
    m_GUI.add(m_currentProfileName);

    m_profilesList->setSize(250, 150);
    m_profilesList->setPosition({bindLeft(m_changeProfileBtn)},
        {bindTop(m_changeProfileBtn) - 156});
    m_profilesList->setVisible(false);
    m_profilesList->setEnabled(false);
    m_GUI.add(m_profilesList);

    setupProfileSwitchers();

    m_saveBtn->getRenderer()->setTexture(m_resources->getTexture(12));
    m_saveBtn->setSize(33, 33);
    m_saveBtn->setPosition({bindRight(m_currentProfileName) + 7},
        {bindTop(m_currentProfileName)});
    m_GUI.add(m_saveBtn);
}

void ProfileEditor::setupBtnsBehaviour() {
    m_changeProfileBtn->onPress([&]{ 
        if(m_profilesList->isEnabled()) {
            m_profilesList->setVisible(false);
            m_profilesList->setEnabled(false);
        } else {
            m_profilesList->setVisible(true);
            m_profilesList->setEnabled(true);
        }
    });

    m_saveBtn->onPress([&]{
        m_profiles->setPageSize(sf::Vector2f{m_pageWidthInput->getText().toFloat(),
            m_pageHeightInput->getText().toFloat()});
        m_profiles->setCutLine(sf::Vector2f{m_cutLineXInput->getText().toFloat(),
            m_cutLineYInput->getText().toFloat()});
        m_profiles->setFirstNoteOffset(m_firstNoteOffsetInput->getText().toFloat());
        m_profiles->setBreaks(sf::Vector2f{m_verticalBreakInput->getText().toFloat(),
            m_horizontalBreakInput->getText().toFloat()});

        m_profiles->changeName(m_currentProfile, m_currentProfileName->getText().toStdString());

        m_profiles->saveProfile(m_currentProfileName->getText().toStdString());

        setupProfileSwitchers();
    });
}

void ProfileEditor::setupProfileSwitchers() {
    m_profilesList->removeAllWidgets();
    m_profileSwitchers.clear();

    for(int i{}; i < m_profiles->getProfilesCount(); ++i) {
        auto element = tgui::Button::create();
        element->setText(m_profiles->getName(i));
        if(m_profileSwitchers.size() != 0) {
            element->setPosition(0, {bindBottom(m_profileSwitchers.back()) + 5});
        }
        m_profilesList->add(element);

        element->onPress(&ProfileEditor::switchProfile, this, element->getText().toStdString());

        m_profileSwitchers.push_back(element);
    }
}

void ProfileEditor::switchProfile(const std::string& profileName) {
    m_currentProfile = profileName;
    m_changeProfileBtn->setText(m_currentProfile);

    m_profiles->switchProfile(profileName);

    setupBtnsLook();

    m_profilesList->setVisible(false);
    m_profilesList->setEnabled(false);
}
