#include "Line.hpp"

namespace cmt {
    Line::Line() {
        m_verts.clear();
    }

    Line::Line(sf::Vector2f start, sf::Vector2f end, sf::Color color) 
        : Line::Line() {

        m_verts.append(sf::Vertex(start));
        m_verts.append(sf::Vertex(end));
        
        setColor(color);
    }

    void Line::setColor(sf::Color color) {
        m_color = color;
        for(int i{0}; i < m_verts.getVertexCount(); ++i) {
            m_verts[i].color = m_color;
        }
    }

    sf::Color Line::getColor() {
        return m_color;
    }

    void Line::render(sf::RenderWindow& target) {
        target.draw(m_verts);
    }
}