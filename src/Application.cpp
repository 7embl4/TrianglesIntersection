#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <ctime>
#include <random>
#include "Figures.h"

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;

std::vector<Triangle> triangles;
std::vector<Polygon> polygons;

void MakeRandomTriangle(int mouse_x, int mouse_y) {
    Triangle triangle(mouse_x, mouse_y);
    triangles.push_back(triangle);
}

void MakeRandomPolygon(int mouse_x, int mouse_y) {
    Polygon polygon(mouse_x, mouse_y);
    polygons.push_back(polygon);
}

int main() {
    sf::ContextSettings settings;
    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    camera.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
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
            if (event.type == sf::Event::MouseButtonReleased) {
                MakeRandomPolygon(event.mouseButton.x + camera.getCenter().x - WINDOW_WIDTH / 2,
                    event.mouseButton.y + camera.getCenter().y - WINDOW_HEIGHT / 2);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    camera.move(0, -40);
                }
                if (event.key.code == sf::Keyboard::S) {
                    camera.move(0, 40);
                }
                if (event.key.code == sf::Keyboard::A) {
                    camera.move(-40, 0);
                }
                if (event.key.code == sf::Keyboard::D) {
                    camera.move(40, 0);
                }
            }
        }
        main_window.setView(camera);
        main_window.clear(sf::Color::White);

        for (size_t i = 0; i != polygons.size(); ++i) {
            main_window.draw(polygons[i]);
        }

        main_window.display();
    }

    return 0;
}
