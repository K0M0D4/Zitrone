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

        // for later
        /*bool load(const std::string& filename);
        bool save();
        bool saveAs();*/

        void addNote();
        void setChord(uint16_t chord);
        void deleteNote();

        void moveActiveLines(sf::Keyboard::Key keyCode);

        // pass already mapped from pixel to coords
        void setActiveLines(sf::Vector2f mousePos);
        
        void render(sf::RenderWindow& target);

    private:
        ResourceManager* m_resources{};
        float m_dpcm{118.1102f};

        // values have to be in pixels, not centimeters, that's why it's multiplied by dpcm
        // outline of the workspace
        sf::RectangleShape m_workspace{sf::Vector2f{21.0f * m_dpcm,
            29.7f * m_dpcm}};

        float m_firstNoteOffset{0.9f * m_dpcm};
        float m_breakBetweenNotesV{0.5f * m_dpcm};
        float m_breakBetweenNotesH{0.9f * m_dpcm};

        Grid m_grid{};
        GridHints m_gridHints{};

        std::vector<Note> m_notes{};
        std::vector<Line> m_noteLines{};

        void sortNotes();

        void calculateLines();

        void addNewNote(const sf::Vector2i& al);

    };
}
