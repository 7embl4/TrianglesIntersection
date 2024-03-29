#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <ctime>
#include <random>
#include <chrono>
#include "Figures.h"
#include "Algorithm.h"

// Window constants
static const size_t WINDOW_WIDTH = 1600;
static const size_t WINDOW_HEIGHT = 900;

// Time constants
static const auto SPAWN_DELAY = std::chrono::milliseconds(300);

std::vector<figures::Polygon> polygons;

void MakeRandomPolygon(int mouse_x, int mouse_y) {
    figures::Polygon polygon(mouse_x, mouse_y);
    polygons.push_back(polygon);
}

int main() {
    sf::ContextSettings settings;
    sf::View camera;
    figures::Polygon intersectionArea;
    camera.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    camera.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    settings.antialiasingLevel = 16;
    sf::RenderWindow main_window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Triangles",
        sf::Style::Close,
        settings
    );

    auto last_spawn_time = std::chrono::system_clock::now();

    srand(time(0));
    while (main_window.isOpen()) {
        sf::Event event;
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                main_window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                auto curr_time = std::chrono::system_clock::now();
                if (curr_time - last_spawn_time > SPAWN_DELAY) {
                    MakeRandomPolygon(event.mouseButton.x + camera.getCenter().x - WINDOW_WIDTH / 2,
                        event.mouseButton.y + camera.getCenter().y - WINDOW_HEIGHT / 2);
                    if (polygons.size() == 1)
                    {
                        intersectionArea = CommonIntersection(polygons, polygons.size());
                    }
                    else if (polygons.size() > 1)
                    {
                        intersectionArea = IntersectionPolygon(polygons[polygons.size() - 1], intersectionArea);
                    }
                    last_spawn_time = std::chrono::system_clock::now();
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case (sf::Keyboard::W):
                        camera.move(0, -40);
                        break;
                    case (sf::Keyboard::S):
                        camera.move(0, 40);
                        break;
                    case (sf::Keyboard::A):
                        camera.move(-40, 0);
                        break;
                    case (sf::Keyboard::D):
                        camera.move(40, 0);
                        break;
                }
            }
        }
        main_window.setView(camera);
        main_window.clear(sf::Color::White);

        for (size_t i = 0; i != polygons.size(); ++i) {
            main_window.draw(polygons[i]);
        }
        main_window.draw(intersectionArea);

        main_window.display();
    }

    return 0;
}
