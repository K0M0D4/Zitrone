#pragma once

#include "Config.hpp"
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
        Project(Config* config, ResourceManager* resources);

        void save();
        void saveAs(const std::string& filename);
        void open(const std::string& filename);
        void exportProj(const std::string& filename); 

        void addNote();
        void setChord(uint16_t chord);
        void deleteNote();

        void moveActiveLines(sf::Vector2i howMuch);

        // pass already mapped from pixel to coords
        void setActiveLines(sf::Vector2f mousePos);

        std::string getName();
        
        void render(sf::RenderWindow& target);

    private:
        ResourceManager* m_resources{};
        float m_dpcm{118.1102f};

        std::string m_name{};

        // outline of the workspace
        sf::RectangleShape m_workspace{};

        float m_firstNoteOffset{};
        float m_breakBetweenNotesV{};
        float m_breakBetweenNotesH{};

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
