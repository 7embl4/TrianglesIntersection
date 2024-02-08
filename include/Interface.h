#pragma once
#include <SFML/Graphics.hpp>
#include "Interface.h"

static size_t WindowWidth = 1500;
static size_t WindowHeight = 900;

class Frame {
private:
	sf::RectangleShape _frame;

public:
	Frame(float width, float height) : _frame(sf::Vector2f(width, height)) {}
	bool contains(float, float);
};