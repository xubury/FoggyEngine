#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

void ProcessEvent(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

int main() {
    std::cout << "Hello World" << std::endl;
    sf::RenderWindow window(sf::VideoMode(640, 480), "Fog");
    while (window.isOpen()) {
        ProcessEvent(window);
    }
    return 0;
}
