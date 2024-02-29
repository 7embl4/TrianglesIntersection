#include "Figures.h"
#include <iostream>

const size_t MAX_RADIUS = 200;
const size_t MIN_RADIUS = 50;
const float MIN_DIFF = 20;

float cross_product(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.y - v2.x * v1.y;
}

Triangle::Triangle(int mouse_x, int mouse_y) : vertices(3) {
	// Задаем радиус, в котором будем рандомить точки
	int radius = rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS;

	// Рандомим две вершины треугольника
	float x1 = rand() % (2 * radius) + (mouse_x - radius);
	float y1 = rand() % (2 * radius) + (mouse_y - radius);
	float x2 = rand() % (2 * radius) + (mouse_x - radius);
	float y2 = rand() % (2 * radius) + (mouse_y - radius);

	// Если вторая вершина слишком близко к прямой 
	// между точками (mouse_x, mouse_y) и (x1, y1),
	// то перегенерируем вторую вершину
	float vector_len = sqrt(pow(mouse_x - x1, 2) + pow(mouse_y - y1, 2));
	float dist = abs(cross_product({ mouse_x - x2, mouse_y - y2 }, { x1 - x2, y1 - y2 })) / abs(vector_len);
	while (dist < MIN_DIFF) {
		x2 = rand() % (2 * radius) + (mouse_x - radius);
		y2 = rand() % (2 * radius) + (mouse_y - radius);
		dist = abs(cross_product({ mouse_x - x2, mouse_y - y2 }, { x1 - x2, y1 - y2 })) / abs(vector_len);
	}
	
	// Находим третью вершину с помощью формулы центра масс
	float x3 = 3 * mouse_x - x1 - x2;
	float y3 = 3 * mouse_y - y1 - y2;

	// Сохраняем вершины
	vertices[0] = { x1, y1 };
	vertices[1] = { x2, y2 };
	vertices[2] = { x3, y3 };

	// Customize
	this->setFillColor(sf::Color::Cyan);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(2);
}

Triangle::Triangle(const sf::Vector2f& v1, const sf::Vector2f& v2, const sf::Vector2f& v3) : vertices(3) {
	vertices[0] = { v1.x, v1.y };
	vertices[1] = { v2.x, v2.y };
	vertices[2] = { v3.x, v3.y };

	// Customize
	this->setFillColor(sf::Color::Yellow);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(2);
}

Polygon::Polygon(const Triangle& tr) : vertices(3), point_count(3) {
	for (size_t i = 0; i != 3; ++i) {
		vertices[i] = tr.getPoint(i);
	}

	// Customize
	this->setFillColor(sf::Color::Red);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(5);
}

Polygon::Polygon(size_t count, const std::vector<sf::Vector2f>& vs) : vertices(count), point_count(count) {
	for (size_t i = 0; i != count; ++i) {
		vertices[i] = { vs[i].x, vs[i].y };
	}

	// Customize
	this->setFillColor(sf::Color::Red);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(5);
}