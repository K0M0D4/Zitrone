#include "Settings.hpp"

Settings::Settings() {}

void Settings::start(sf::RenderWindow& window) {


    while(window.isOpen()) {
        if(!update(window)) return;
    
        render(window);
    }
}

bool Settings::update(sf::RenderWindow& window) {
    sf::Event event{};
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) return false;
    }
    return true;
}

void Settings::render(sf::RenderWindow& target) {
    target.clear(sf::Color::Blue);

    target.display();
}
