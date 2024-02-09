#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <ctime>
#include <random>
#include "Figures.h"
#include "Interface.h"

std::vector<Triangle> triangles;

void MakeRandomTriangle(int mouse_x, int mouse_y) {
    Triangle triangle(mouse_x, mouse_y);
    triangles.push_back(triangle);
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow main_window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Triangles",
        sf::Style::Close,
        settings
    );

    srand(time(0));
    while (main_window.isOpen()) {
        sf::Event event;
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                main_window.close();
            else if (event.type == sf::Event::MouseButtonReleased) {
                MakeRandomTriangle(event.mouseButton.x, event.mouseButton.y);
            }
        }
        
        main_window.clear(sf::Color::White);

        for (size_t i = 0; i != triangles.size(); ++i) {
            main_window.draw(triangles[i]);
        }

        main_window.display();
    }

    return 0;
}
