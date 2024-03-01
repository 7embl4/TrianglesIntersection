#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"

class Triangle : public sf::Shape {
private:
    std::vector<sf::Vector2f> vertices;

public:
    Triangle(int, int);
    Triangle(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);  // For tests

    virtual size_t getPointCount() const {
        return 3;
    }
    sf::Vector2f getPoint(size_t index) const {
        return vertices[index];
    }
};

class Polygon : public sf::Shape {
private:
    std::vector<sf::Vector2f> vertices;
    size_t point_count;

public:
    Polygon(const Triangle&);
    Polygon(int, int);
    Polygon(size_t, const std::vector<sf::Vector2f>&);

    virtual size_t getPointCount() const {
        return point_count;
    }

    sf::Vector2f getPoint(size_t index) const {
        return vertices[index];
    }
};