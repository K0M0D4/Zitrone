#include "DashLine.hpp"

namespace cmt {
    DashLine::DashLine() {
        m_verts = sf::VertexArray(sf::Lines, 0);
        m_verts.clear();
    }

    DashLine::DashLine(sf::Vector2f start, sf::Vector2f end,
        float dashLength, sf::Color color) {

        m_verts = sf::VertexArray(sf::Lines, 1);
        m_verts.clear();

        float a{end.x - start.x};
        float b{end.y - start.y};
        double angle{std::atan2(b, a)};
        double totalLength{a / sin(angle)};
        uint32_t dashOcurrencies{static_cast<uint32_t>(std::floor(totalLength / dashLength))};
        float segmentWidth{dashLength * static_cast<float>(sin(angle))};
        float segmentHeight{dashLength * static_cast<float>(cos(angle))};

        m_verts.append(sf::Vertex(start));

        for(int i{1}; i < dashOcurrencies; ++i) {
            m_verts.append(sf::Vertex(
                sf::Vector2f(segmentWidth * i + start.x,
                    segmentHeight * i + start.y)));
        }
        
        setColor(color);
    }

    void DashLine::setColor(sf::Color color) {
        m_color = color;
        for(int i{0}; i <= m_verts.getVertexCount(); ++i) {
            m_verts[i].color = m_color;
        }
    }

    sf::Color DashLine::getColor() {
        return m_color;
    }

    void DashLine::render(sf::RenderWindow& target) {
        target.draw(m_verts);
    }
}