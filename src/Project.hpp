#pragma once

#include "Grid.hpp"
#include "GridHints.hpp"
#include "Note.hpp"

#include "fw/Line.hpp"
#include "fw/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace cmt {
    class Project {
    public:
        Project();
        Project(const std::string& name, ResourceManager* resources);

        void save();
        void saveAs(const std::string& filename);
        void open(const std::string& filename);

        void addNote();
        void setChord(uint16_t chord);
        void deleteNote();

        void moveActiveLines(sf::Keyboard::Key keyCode);

        // pass already mapped from pixel to coords
        void setActiveLines(sf::Vector2f mousePos);

        std::string getName();
        
        void render(sf::RenderWindow& target);

    private:
        ResourceManager* m_resources{};
        float m_dpcm{118.1102f};

        std::string m_name{};

        // values have to be in pixels, not centimeters, that's why it's multiplied by dpcm
        // outline of the workspace
        sf::RectangleShape m_workspace{sf::Vector2f{21.0f * m_dpcm,
            29.7f * m_dpcm}};

        float m_firstNoteOffset{0.9f * m_dpcm};
        float m_breakBetweenNotesV{0.5f * m_dpcm};
        float m_breakBetweenNotesH{0.9f * m_dpcm};

        float m_cutXPos{17.0f * m_dpcm};
        float m_cutYPos{20.0f * m_dpcm};

        Line m_cutLine{sf::Vector2f{m_cutXPos, 0.0f},
            sf::Vector2f{m_workspace.getSize().x, m_workspace.getSize().y
            - m_cutYPos}, sf::Color::Red};

        Grid m_grid{};
        GridHints m_gridHints{};

        std::vector<Note> m_notes{};
        std::vector<Line> m_noteLines{};

        void sortNotes();

        void calculateLines();

        void addNewNote(const sf::Vector2i& al);

        void processOpenInput(const std::string& data);

    };
}
