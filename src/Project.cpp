#include "Project.hpp"

namespace cmt {
    Project::Project() {}

    Project::Project(const std::string& name, ResourceManager* resources) {
        m_resources = resources;
        m_grid = Grid{m_workspace.getSize(), m_breakBetweenNotesV,
            m_breakBetweenNotesH, m_firstNoteOffset, m_resources};
        m_workspace.setOutlineThickness(5);
        m_workspace.setFillColor(sf::Color::Transparent);
        m_workspace.setOutlineColor(m_resources->getTheme(0).getColor(4));

        m_gridHints = GridHints(m_resources);
        m_gridHints.calculate(m_workspace.getSize(), m_breakBetweenNotesV,
            m_firstNoteOffset);
        m_gridHints.move(sf::Vector2f(m_firstNoteOffset, 0.0f));
    }

    void Project::addNote() {        
        if(m_notes.size() == 0) {
            addNewNote(m_grid.getActiveLines());
        } else {
            bool addNew{true};
            
            sf::Vector2i al{m_grid.getActiveLines()};
            for(uint16_t i{}; i < m_notes.size(); ++i) {
                if(m_notes.at(i).getCoords().y == al.y) {
                    addNew = false;
                    m_notes.at(i).setPos(sf::Vector2f{
                        al.x * m_breakBetweenNotesV + m_firstNoteOffset,
                        m_notes.at(i).getPos().y}, al);
                    break;
                }
            }

            if(addNew) addNewNote(m_grid.getActiveLines());

            sortNotes();
            calculateLines();
        }
    }

    void Project::setChord(uint16_t chord) {
        sf::Vector2i al{m_grid.getActiveLines()};

        for(uint16_t i{}; i < m_notes.size(); ++i) {
            if(m_notes.at(i).getCoords() == al) {
                m_notes.at(i).setChord(chord);
                break;
            }
        }
    }

    void Project::deleteNote() {
        sf::Vector2i al{m_grid.getActiveLines()};

        for(uint16_t i{}; i < m_notes.size(); ++i) {
            if(m_notes.at(i).getCoords() == al) {
                m_notes.erase(m_notes.begin() + i);
                m_notes.shrink_to_fit();
                break;
            }
        }

        calculateLines();
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
            - m_firstNoteOffset + m_breakBetweenNotesV / 2.0f) / m_breakBetweenNotesV,
            (mousePos.y - m_breakBetweenNotesH / 2.0f) / m_breakBetweenNotesH));
    }

    void Project::render(sf::RenderWindow& target) {
        target.draw(m_workspace);
        m_grid.render(target);

        for(auto& line : m_noteLines) {
            line.render(target);
        }
        for(auto& note : m_notes) {
            note.render(target);
        }

        m_gridHints.setPos(sf::Vector2f(m_gridHints.getPos().x,
            target.mapPixelToCoords(sf::Vector2i{0, static_cast<int32_t>(
            target.getSize().y) - 30}).y));
        m_gridHints.render(target);
    }

    void Project::sortNotes() {
        for(uint32_t i{}; i < m_notes.size(); ++i) {
            for(uint32_t j{i + 1}; j < m_notes.size(); ++j) {
                Note temp{sf::Vector2f{}, sf::Vector2i{},
                    m_resources->getFont(0),
                    m_resources->getTheme(0).getColor(6)};
                if(m_notes.at(j).getCoords().y < m_notes.at(i).getCoords().y) {
                    temp = m_notes.at(i);
                    m_notes.at(i) = m_notes.at(j);
                    m_notes.at(j) = temp;
                }
            }
        }
    }

    void Project::calculateLines() {
        if(m_notes.size() > 1) {
            m_noteLines.clear();
            for(uint16_t i{1}; i < m_notes.size(); ++i) {
                m_noteLines.emplace_back(Line(m_notes.at(i - 1).getPos(),
                    m_notes.at(i).getPos(),
                    m_resources->getTheme(0).getColor(7)));
            }
        }
    }

    void Project::addNewNote(const sf::Vector2i& al) {
        m_notes.emplace_back(Note{sf::Vector2f{
            al.x * m_breakBetweenNotesV + m_firstNoteOffset,
            (al.y + 1) * m_breakBetweenNotesH}, al,
            m_resources->getFont(0),
            m_resources->getTheme(0).getColor(6)});
    }
}
