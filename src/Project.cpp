#include "Project.hpp"

#include <iostream>

namespace cmt {
    Project::Project() : Project("project_name") {}

    Project::Project(const std::string& name) {
        m_workspace.setOutlineThickness(5);
        m_workspace.setFillColor(sf::Color::Transparent);
        m_workspace.setOutlineColor(sf::Color::White);
    }

    void Project::addNote() {
        sf::Vector2i al{m_grid.getActiveLines()};
        
        if(m_notes.size() == 0) {
            m_notes.emplace_back(Note{sf::Vector2f{
                al.x * m_breakBetweenNotesV + m_firstNoteOffset,
                (al.y + 1) * m_breakBetweenNotesH}, al});
        } else {
            bool addNew{true};
            
            for(uint16_t i{}; i < m_notes.size(); ++i) {
                if(m_notes.at(i).getCoords().y == al.y) {
                    addNew = false;
                    m_notes.at(i).setPos(sf::Vector2f{
                        al.x * m_breakBetweenNotesV + m_firstNoteOffset,
                        (al.y + 1) * m_breakBetweenNotesH}, al);
                    break;
                }
            }

            if(addNew) {
                m_notes.emplace_back(Note{sf::Vector2f{
                    al.x * m_breakBetweenNotesV + m_firstNoteOffset,
                    (al.y + 1) * m_breakBetweenNotesH}, al});
            }

            sortNotes();

            for(auto note : m_notes) {
                std::cout << note.getCoords().y << ' ';
            }
            std::cout << '\n';
        }
    }

    void Project::moveActiveLines(sf::Keyboard::Key keyCode) {
        if(keyCode == sf::Keyboard::Right) {
            m_grid.moveActiveLines(sf::Vector2i(1, 0));
        } else if(keyCode == sf::Keyboard::Left) {
            m_grid.moveActiveLines(sf::Vector2i(-1, 0));
        } else if(keyCode == sf::Keyboard::Up) {
            m_grid.moveActiveLines(sf::Vector2i(0, -1));
        } else if(keyCode == sf::Keyboard::Down) {
            m_grid.moveActiveLines(sf::Vector2i(0, 1));
        }
    }

    void Project::setActiveLines(sf::Vector2f mousePos) {
        m_grid.setActiveLines(sf::Vector2i((mousePos.x
            - m_firstNoteOffset + m_breakBetweenNotesV / 2.0f)
            / m_breakBetweenNotesV,
            (mousePos.y - m_breakBetweenNotesH / 2.0f)
            / m_breakBetweenNotesH));
    }

    void Project::render(sf::RenderWindow& target) {
        target.draw(m_workspace);
        m_grid.render(target);

        for(auto& note : m_notes) {
            note.render(target);
        }
    }

    void Project::sortNotes() {
        for(uint32_t i{}; i < m_notes.size(); ++i) {
            for(uint32_t j{i + 1}; j < m_notes.size(); ++j)
            {
                Note temp{sf::Vector2f{}, sf::Vector2i{}};
                if(m_notes.at(j).getCoords().y < m_notes.at(i).getCoords().y) {
                    temp = m_notes.at(i);
                    m_notes.at(i) = m_notes.at(j);
                    m_notes.at(j) = temp;
                }
            }
        }
    }
}