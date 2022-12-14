#pragma once

#include "Note.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace cmt {
    class Project {
    public:
        Project();
        Project(const std::string& name);

        // for later
        /*bool load(const std::string& filename);
        bool save();
        bool saveAs();*/

        void addNote();
        void emplaceNote();
        void addChord();
        void deleteNote();

        void renderNotes(sf::RenderWindow& target);

    private:
        std::vector<Note> m_notes{};

    };
}