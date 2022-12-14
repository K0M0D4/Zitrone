#include "Project.hpp"

namespace cmt {
    Project::Project() : Project("project_name") {}

    Project::Project(const std::string& name) {
        m_workspace.setOutlineThickness(5);
        m_workspace.setFillColor(sf::Color::Transparent);
        m_workspace.setOutlineColor(sf::Color::White);
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
    }
}