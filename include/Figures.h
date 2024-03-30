#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"

float cross_product(const sf::Vector2f&, const sf::Vector2f&);

namespace figures {
    class Polygon : public sf::Shape {
    private:
        std::vector<sf::Vector2f> vertices;
        size_t point_count;

    public:
        Polygon() {}
        Polygon(int, int);
        Polygon(size_t, const std::vector<sf::Vector2f>&);

        virtual size_t getPointCount() const {
            return point_count;
        }

        sf::Vector2f getPoint(size_t index) const {
            return vertices[index];
        }
    };

    class IntersectionArea : public sf::Shape {
    private:
        std::vector<sf::Vector2f> vertices;

    public:
        IntersectionArea() : vertices(0) {
            this->setFillColor(sf::Color::Red);
            this->setOutlineColor(sf::Color::Black);
            this->setOutlineThickness(3);
        }
        IntersectionArea(const Polygon& polygon);
    
        virtual size_t getPointCount() const {
            return vertices.size();
        }

        sf::Vector2f getPoint(size_t index) const {
            return vertices[index];
        }
    };
}
