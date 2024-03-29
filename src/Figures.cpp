#include "Figures.h"
#include <iostream>
#include <algorithm>

const size_t MAX_RADIUS = 200;
const size_t MIN_RADIUS = 50;
const float MIN_DIFF = 20;

float cross_product(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.y - v2.x * v1.y;
}

bool is_not_convex(
	const sf::Vector2f& prelast_point, 
	const sf::Vector2f& last_point, 
	const sf::Vector2f& curr_point) 
{
	sf::Vector2f v1 = last_point - prelast_point;
	sf::Vector2f v2 = curr_point - last_point;
	return cross_product(v1, v2) < 0;
}

std::vector<sf::Vector2f> convex_hull(std::vector<sf::Vector2f>& points) {
	// Find the most left-down point
	sf::Vector2f p0 = points[0];
	size_t p0_index = 0;
	for (size_t i = 1; i != points.size(); ++i) {
		if (points[i].x == p0.x && points[i].y > p0.y || points[i].x < p0.x) {
			p0 = points[i];
			p0_index = i;
		}
	}

	// Erase p0 from vector of points, since we sort only other points.
	// Sorting with p0 will break the algorithm
	points.erase(points.begin() + p0_index);

	// Sort points by angle relative to p0
	std::sort(
		points.begin(),
		points.end(),
		[&p0](const sf::Vector2f& p1, const sf::Vector2f& p2) {
			return cross_product(p1 - p0, p2 - p0) > 0;
		});

	// Find convex hull
	std::vector<sf::Vector2f> ans;
	ans.push_back(p0);
	for (size_t i = 0; i != points.size(); ++i) {
		while (ans.size() > 1 && is_not_convex(ans[ans.size() - 2], ans[ans.size() - 1], points[i])) {
			ans.pop_back();
		}
		ans.push_back(points[i]);
	}

	return ans;
}

namespace figures {
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

	Polygon::Polygon(int mouse_x, int mouse_y) {
		// Get random radius of polygon
		int radius = rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS;

		// Generate 10 random points in radius
		std::vector<sf::Vector2f> points;
		for (size_t i = 0; i != 10; ++i) {
			float x = rand() % (2 * radius) + (mouse_x - radius);
			float y = rand() % (2 * radius) + (mouse_y - radius);
			points.push_back({ x, y });
		}

		// Find convex hull of these points using Graham algorithm
		vertices = convex_hull(points);
		point_count = vertices.size();

		// Сustomize
		this->setFillColor(sf::Color::Cyan);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(2);
	}

	Polygon::Polygon(const Triangle& tr) : vertices(3), point_count(3) {
		for (size_t i = 0; i != 3; ++i) {
			vertices[i] = tr.getPoint(i);
		}

		// Customize
		this->setFillColor(sf::Color::Blue);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(2);
	}

	Polygon::Polygon(size_t count, const std::vector<sf::Vector2f>& vs) : vertices(count), point_count(count) {
		for (size_t i = 0; i != count; ++i) {
			vertices[i] = { vs[i].x, vs[i].y };
		}

		// Customize
		this->setFillColor(sf::Color::Blue);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(2);
	}

	IntersectionArea::IntersectionArea(const Polygon& polygon) {
		this->vertices.reserve(polygon.getPointCount());
		for (size_t i = 0; i != polygon.getPointCount(); ++i) {
			this->vertices[i] = polygon.getPoint(i);
		}

		// Customize
		this->setFillColor(sf::Color::Red);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(3);
	}
}
