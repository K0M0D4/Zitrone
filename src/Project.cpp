#include "Project.hpp"

#include <fstream>
#include <sstream>

Project::Project() {}

Project::Project(Config* config, cmt::ResourceManager* resources) {

    m_resources = resources;

    m_workspace.setSize(config->getPageSize() * m_dpcm);

    m_firstNoteOffset = config->getFirstNoteOffset() * m_dpcm;
    m_breakBetweenNotesV = config->getBreaks().x * m_dpcm;
    m_breakBetweenNotesH = config->getBreaks().y * m_dpcm;

    m_grid = Grid{m_workspace.getSize(), m_breakBetweenNotesV,
        m_breakBetweenNotesH, m_firstNoteOffset, m_resources};
    m_workspace.setOutlineThickness(5);
    m_workspace.setFillColor(sf::Color::Transparent);
    m_workspace.setOutlineColor(m_resources->getTheme(0).getColor(4));

    m_gridHints = GridHints(m_resources);
    m_gridHints.calculate(m_workspace.getSize(), m_breakBetweenNotesV,
        m_firstNoteOffset);
    m_gridHints.move(sf::Vector2f{m_firstNoteOffset, 0.0f});

    m_cutLine = cmt::Line{sf::Vector2f{config->getCutLine().x * m_dpcm, 0.0f},
        sf::Vector2f{m_workspace.getSize().x, m_workspace.getSize().y
        - config->getCutLine().y * m_dpcm}, sf::Color::Red};
}

void Project::save() {
    std::ofstream file(m_name);
    if(!file.good()) 
        throw std::runtime_error("Can't save to file: " + m_name);

    for(auto& note : m_notes) {
        file << note.getCoords().x << '.';
        file << note.getCoords().y << '.';
        file << note.getChord() << '\n';
    }
    
    file.close();
}

void Project::saveAs(const std::string& filename) {
    m_name = filename;
    save();
}

void Project::open(const std::string& filename) {
    m_name = filename;
    m_notes.clear();

    std::ifstream file(filename);
    if(!file.good()) 
        throw std::runtime_error("Can't load file: " + m_name);

    std::string buffer{};

    while(getline(file, buffer)) {
        processOpenInput(buffer);
    }
    
    file.close();
}

void Project::exportProj(const std::string& filename) {
    sf::RenderTexture buffer{};
    if(!buffer.create(m_workspace.getSize().x, m_workspace.getSize().y))
        throw std::runtime_error("Error: Can't create buffer for exporting\n");

    buffer.clear(sf::Color::White);

    render(buffer);

    buffer.display();

    sf::Image image{};
    image.create(m_workspace.getSize().x, m_workspace.getSize().y);

    image = buffer.getTexture().copyToImage();

    if(!image.saveToFile(filename))
        throw std::runtime_error("Error: Can't export project\n");

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

void Project::setChordPosition(int position) {
    sf::Vector2i al{m_grid.getActiveLines()};

    for(uint16_t i{}; i < m_notes.size(); ++i) {
        if(m_notes.at(i).getCoords() == al && m_notes.at(i).getChord() != 0) {
            m_notes.at(i).setChordPos(position);
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

void Project::moveNotesRight() {
    for(auto& note : m_notes) {
        note.setPos(sf::Vector2f{note.getPos().x + m_breakBetweenNotesV,
            note.getPos().y}, sf::Vector2i{note.getCoords().x + 1,
            note.getCoords().y});
    }

    calculateLines();
}

void Project::moveNotesLeft() {
    for(auto& note : m_notes) {
        note.setPos(sf::Vector2f{note.getPos().x - m_breakBetweenNotesV,
            note.getPos().y}, sf::Vector2i{note.getCoords().x - 1,
            note.getCoords().y});
    }

    calculateLines();
}

void Project::moveNotesUp() {
    for(auto& note : m_notes) {
        note.setPos(sf::Vector2f{note.getPos().x, note.getPos().y
            - m_breakBetweenNotesH}, sf::Vector2i{note.getCoords().x,
            note.getCoords().y - 1});
    }

    calculateLines();
}

void Project::moveNotesDown() {
    for(auto& note : m_notes) {
        note.setPos(sf::Vector2f{note.getPos().x, note.getPos().y
            + m_breakBetweenNotesH}, sf::Vector2i{note.getCoords().x,
            note.getCoords().y + 1});
    }

    calculateLines();
}

sf::Vector2i Project::moveActiveLines(sf::Vector2i howMuch) {
    m_grid.moveActiveLines(howMuch);
    return m_grid.getActiveLines();
}

sf::Vector2i Project::setActiveLines(sf::Vector2f mousePos) {
    m_grid.setActiveLines(sf::Vector2i((mousePos.x
        - m_firstNoteOffset + m_breakBetweenNotesV / 2.0f) / m_breakBetweenNotesV,
        (mousePos.y - m_breakBetweenNotesH / 2.0f) / m_breakBetweenNotesH));
    return m_grid.getActiveLines();
}

void Project::setActiveLines(sf::Vector2i lines) {
    m_grid.setActiveLines(lines);
}

sf::Vector2i Project::getActiveLines() {
    return m_grid.getActiveLines();
}

std::string Project::getName() {
    return m_name;
}

sf::Vector2f Project::getNotePosAtAL() {
    for(auto& note : m_notes) {
        if(note.getCoords() == m_grid.getActiveLines()) {
            return note.getPos();
        }
    }

    return sf::Vector2f{};
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

    m_cutLine.render(target);

    m_gridHints.setPos(sf::Vector2f(m_gridHints.getPos().x,
        target.mapPixelToCoords(sf::Vector2i{0, static_cast<int32_t>(
        target.getSize().y) - 30}).y));

    m_gridHints.render(target);
}

void Project::render(sf::RenderTexture& target) {
    sf::Color tempLineColor = m_noteLines.at(0).getColor();
    sf::Color tempNoteColor = m_notes.at(0).getColor();

    for(auto& line : m_noteLines) {
        line.setColor(sf::Color::Black);
        line.render(target);
        line.setColor(tempLineColor);
    }
    for(auto& note : m_notes) {
        note.setColor(sf::Color::Black);
        note.render(target);
        note.setColor(tempNoteColor);
    }

    m_cutLine.render(target);
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
            m_noteLines.emplace_back(cmt::Line(m_notes.at(i - 1).getPos(),
                m_notes.at(i).getPos(),
                m_resources->getTheme(0).getColor(7)));
        }
    } else {
        m_noteLines.clear();
    }
}

void Project::addNewNote(const sf::Vector2i& al) {
    m_notes.emplace_back(Note{sf::Vector2f{
        al.x * m_breakBetweenNotesV + m_firstNoteOffset,
        (al.y + 1) * m_breakBetweenNotesH}, al,
        m_resources->getFont(0),
        m_resources->getTheme(0).getColor(6)});
}

void Project::processOpenInput(const std::string& data) {
    std::stringstream ss(data);
    std::string word;
    std::vector<std::string> tokens;

    while (!ss.eof()) {
        getline(ss, word, '.');
        tokens.push_back(word);
    }

    m_grid.setActiveLines(sf::Vector2i{std::stoi(tokens.at(0)),
        std::stoi(tokens.at(1))});
    addNote();
    setChord(std::stoi(tokens.at(2)));
}
