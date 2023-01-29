#include "Theme.hpp"

namespace cmt {
    Theme::Theme(const std::string& filepath) {
        load(filepath);
    }

    void Theme::load(const std::string& filepath) {
        std::ifstream file{filepath, std::ios::binary | std::ios::ate};

        uint8_t data[m_colorsCount * 3]{};

        if(file.good()) {
            std::streampos filesize{file.tellg()};
            char* filebuffer = new char[filesize];

            file.seekg(0, std::ios::beg);
            file.read(filebuffer, filesize);
            file.close();

            for(uint32_t i{}; i < filesize; ++i) {
                data[i] = filebuffer[i];
            }

            delete[] filebuffer;
        }

        for(uint16_t i{}; i < m_colorsCount; ++i) {
            m_colors.at(i) = sf::Color{data[i * 3], data[i * 3 + 1], data[i * 3 + 2]};
        }
    }

    sf::Color Theme::getColor(uint16_t which) {
        if(which >= 0 && which < m_colorsCount)
            return m_colors.at(which);
        return m_colors.at(0);
    }
}