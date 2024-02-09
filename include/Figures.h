#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"

class Triangle : public sf::Shape {
private:
    std::vector<sf::Vector2f> vertices;
    static const size_t MAX_RADIUS;
    static const size_t MIN_RADIUS;

public:
    Triangle(int, int);
    Triangle(sf::Vector2f, sf::Vector2f, sf::Vector2f);  // For tests

    virtual size_t getPointCount() const {
        return 3;
    }
    sf::Vector2f getPoint(size_t index) const {
        return vertices[index];
    }
};
