#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figures.h"
#include "Algorithm.h"

float kFind(sf::Vector2f, sf::Vector2f);

float bFind(sf::Vector2f, sf::Vector2f);

sf::Vector2f IntersectionPoint(float, float, float, float);

bool AreaCheckingPoint(float, float, sf::Vector2f, sf::Vector2f);

Polygon IntersectionPolygon(Polygon, float, float, sf::Vector2f);