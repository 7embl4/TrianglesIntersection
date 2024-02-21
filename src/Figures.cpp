#include "Figures.h"
#include "Interface.h"
#include <iostream>

const size_t Triangle::MAX_RADIUS = 200;
const size_t Triangle::MIN_RADIUS = 20;

Triangle::Triangle(int mouse_x, int mouse_y) : vertices(3) {
	// TODO: Не спавнить за границами
	// Как вариант не спавнить треугольник вообще, если он слишком близко к границе

	// Задаем радиус, в котором будем рандомить точки
	size_t radius = std::min({ 
		rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS,
		WINDOW_WIDTH - mouse_x,
		(size_t)mouse_x,
		WINDOW_HEIGHT - mouse_y,
		(size_t)mouse_y
	});

	// Рандомим две вершины треугольника
	float x1 = rand() % (2 * radius) + (mouse_x - radius);
	float y1 = rand() % (2 * radius) + (mouse_y - radius);
	float x2 = rand() % (2 * radius) + (mouse_x - radius);
	float y2 = rand() % (2 * radius) + (mouse_y - radius);

	// Если вершины на одной линии с центор масс, 
	// То двигаем вторую вершину на рандомное (в радиусе) расстояние по оси абсцисс
	// В ту сторону, где "больше места"
	if ((x1 == x2) || (y1 == y2) || (mouse_x - x1) / (x2 - x1) == (mouse_x - y1) / (y2 - y1)) {
		if (x2 - (mouse_x - radius) < mouse_x + radius - x2) {
			x2 += rand() % static_cast<size_t>(x2 - (mouse_x - radius));
		}
		else {
			x2 += rand() % static_cast<size_t>((mouse_x + radius) - x2);
		}
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

Triangle::Triangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3) : vertices(3) {
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
}

Polygon::Polygon(size_t count, std::vector<sf::Vector2f> vs) : vertices(count), point_count(count) {
	for (size_t i = 0; count; i++) {
		vertices[i] = { vs[i].x, vs[i].y };
	}
}