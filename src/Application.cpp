#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <ctime>
#include <random>
#include "Figures.h"
#include "Interface.h"

std::vector<Triangle> triangles;

void MakeRandomTriangle(float x, float y) {
    Triangle triangle(x, y);

    // Если точка треугольника за границей, то он будет "пустой"
    if (triangle.getPointCount() == 0) {
        return;
    }

    triangle.setFillColor(sf::Color::Cyan);
    triangle.setOutlineColor(sf::Color::Black);
    triangle.setOutlineThickness(2);
    triangles.push_back(triangle);
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow main_window(
        sf::VideoMode(WindowWidth, WindowHeight), 
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
