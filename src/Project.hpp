#pragma once

#include "ProfileManager.hpp"
#include "Grid.hpp"
#include "GridHints.hpp"
#include "Note.hpp"

#include "fw/Line.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class Project {
public:
    Project();
    Project(ProfileManager* profiles, cmt::ResourceManager* resources);

    void save();
    void saveAs(const std::string& filename);
    void open(const std::string& filename);
    void exportProj(const std::string& filename);

    void reloadProfile(ProfileManager* profiles);

    void addNote();
    void setChord(uint16_t chord);
    void setChordPosition(int position);
    void deleteNote();

    void moveNotesRight();
    void moveNotesLeft();
    void moveNotesUp();
    void moveNotesDown();

    sf::Vector2i moveActiveLines(sf::Vector2i howMuch);

    // pass already mapped from pixel to coords
    sf::Vector2i setActiveLines(sf::Vector2f mousePos);
    void setActiveLines(sf::Vector2i lines);

    sf::Vector2i getActiveLines();
    std::string getName();
    sf::Vector2f getNotePosAtAL();

    bool isALValidforChordPos();
    
    void render(sf::RenderWindow& target);

private:
    cmt::ResourceManager* m_resources{};
    float m_dpcm{118.1102f};

    std::string m_name{};

    // outline of the workspace
    sf::RectangleShape m_workspace{};

    float m_firstNoteOffset{};
    float m_breakBetweenNotesV{};
    float m_breakBetweenNotesH{};

    cmt::Line m_cutLine{};

    Grid m_grid{};
    GridHints m_gridHints{};

    std::vector<Note> m_notes{};
    std::vector<cmt::Line> m_noteLines{};

    // for exporting
    void render(sf::RenderTexture& target);

    void sortNotes();

    void calculateLines();

    void addNewNote(const sf::Vector2i& al);

    void processOpenInput(const std::string& data);

};
