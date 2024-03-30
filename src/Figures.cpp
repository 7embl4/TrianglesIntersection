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

		// Сustomize
		this->setFillColor(sf::Color::Cyan);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(2);
	}

	Polygon::Polygon(size_t count, const std::vector<sf::Vector2f>& vs) : vertices(count) {
		for (size_t i = 0; i != count; ++i) {
			vertices[i] = { vs[i].x, vs[i].y };
		}

		// Customize
		this->setFillColor(sf::Color::Blue);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(2);
	}
}
