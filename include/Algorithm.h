#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"
#include "Algorithm.h"

float kFind(sf::Vector2f, sf::Vector2f);

float bFind(sf::Vector2f, sf::Vector2f);

sf::Vector2f IntersectionPoint(float, float, float, float);

bool PointChecking(float&, float&, const sf::Vector2f&, const sf::Vector2f&);

bool AreaChecking(float&, float&, const sf::Vector2f&, const sf::Vector2f&);

Polygon IntersectionArea(const Polygon&, float&, float&, const sf::Vector2f&);

Polygon IntersectionPolygon(const Triangle&, const Polygon&);

Polygon CommonIntersection(const std::vector<Triangle>&, size_t&);