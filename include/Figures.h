#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"

float cross_product(const sf::Vector2f&, const sf::Vector2f&);

namespace figures {
    class Polygon : public sf::Shape {
    private:
        std::vector<sf::Vector2f> vertices;

    public:
        Polygon() {}
        Polygon(int, int);
        Polygon(size_t, const std::vector<sf::Vector2f>&);

        virtual size_t getPointCount() const {
            return vertices.size();
        }

        sf::Vector2f getPoint(size_t index) const {
            return vertices[index];
        }

        void clear() {
            if (!vertices.empty()) {
                vertices.clear();
            }
        }
    };
}
