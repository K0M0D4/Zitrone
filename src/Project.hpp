#pragma once

#include "Grid.hpp"
#include "Note.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace cmt {
    class Project {
    public:
        Project(const std::string& name);
        Project();

        // for later
        /*bool load(const std::string& filename);
        bool save();
        bool saveAs();*/

        void addNote();
        void emplaceNote();
        void addChord();
        void deleteNote();

        void moveActiveLines(sf::Keyboard::Key keyCode);

        // pass already mapped from pixel to coords
        void setActiveLines(sf::Vector2f mousePos);

        void render(sf::RenderWindow& target);

    private:
        float m_dpcm{118.1102f};

        // values have to be in pixels, not centimeters
        // outline of the workspace
        sf::RectangleShape m_workspace{sf::Vector2f{21.0f * m_dpcm,
            29.7f * m_dpcm}};

        float m_firstNoteOffset{0.9f * m_dpcm};
        float m_breakBetweenNotesV{0.5f * m_dpcm};
        float m_breakBetweenNotesH{0.9f * m_dpcm};

        Grid m_grid{m_workspace.getSize(), m_breakBetweenNotesV,
            m_breakBetweenNotesH, m_firstNoteOffset};

        std::vector<Note> m_notes{};

    };
}