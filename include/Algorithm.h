#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"
#include "Algorithm.h"

float aFind(const sf::Vector2f&, const sf::Vector2f&);

float bFind(const sf::Vector2f&, const sf::Vector2f&);

float cFind(const sf::Vector2f&, const sf::Vector2f&);

sf::Vector2f IntersectionPoint(float, float, float, float, float, float);

bool PointChecking(float, float, float, const sf::Vector2f&, const sf::Vector2f&);

bool AreaChecking(float, float, float, const sf::Vector2f&, const sf::Vector2f&);

figures::Polygon IntersectionArea(const figures::Polygon&, float, float, float, const sf::Vector2f&);

figures::Polygon IntersectionPolygon(const figures::Triangle&, const figures::Polygon&);

figures::Polygon CommonIntersection(const std::vector<figures::Triangle>&, size_t);