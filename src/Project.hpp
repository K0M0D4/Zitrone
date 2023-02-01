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
        Project(sf::Vector2f workspaceSize,
            ResourceManager* resources);

        void save();
        void saveAs(const std::string& filename);
        void open(const std::string& filename);
        void exportProj(const std::string& filename); 

        void addNote();
        void setChord(uint16_t chord);
        void deleteNote();

        void moveActiveLines(sf::Keyboard::Key keyCode);

        // pass already mapped from pixel to coords
        void setActiveLines(sf::Vector2f mousePos);

        void setCutLine(sf::Vector2f values);

        std::string getName();
        
        void render(sf::RenderWindow& target);

    private:
        ResourceManager* m_resources{};
        float m_dpcm{118.1102f};

        std::string m_name{};

        // values have to be in pixels, not centimeters, that's why it's multiplied by dpcm
        // outline of the workspace
        sf::RectangleShape m_workspace{};

        float m_firstNoteOffset{1.3f * m_dpcm};
        float m_breakBetweenNotesV{0.5f * m_dpcm};
        float m_breakBetweenNotesH{0.9f * m_dpcm};

        float m_cutXPos{12.8f * m_dpcm};
        float m_cutYPos{16.7f * m_dpcm};

        Line m_cutLine{};

        Grid m_grid{};
        GridHints m_gridHints{};

        std::vector<Note> m_notes{};
        std::vector<Line> m_noteLines{};

        // for exporting
        void render(sf::RenderTexture& target);

        void sortNotes();

        void calculateLines();

        void addNewNote(const sf::Vector2i& al);

        void processOpenInput(const std::string& data);

    };
}
