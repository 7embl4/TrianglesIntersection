#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"

bool IsPointInZone(float, float);

class Triangle : public sf::Shape {
private:
    sf::ConvexShape tr;
    static const size_t MaxRadius;  // Radius for random triangle generating 
    static const size_t MinRadius;

public:
    Triangle() : tr(3) {}
    Triangle(int, int);
    Triangle(sf::Vector2f, sf::Vector2f, sf::Vector2f);  // For tests

    virtual size_t getPointCount() const {
        return 3;
    }
    sf::Vector2f getPoint(size_t index) const {
        return tr.getPoint(index);
    }
};
