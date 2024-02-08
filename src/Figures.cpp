#include "Figures.h"
#include "Interface.h"

const size_t Triangle::MaxRadius = 200;
const size_t Triangle::MinRadius = 20;

bool IsPointInZone(float x, float y) {
	if (x < 0 || y < 0 || x > WindowWidth || y > WindowHeight) {
		return false;
	}
	return true;
}

Triangle::Triangle(int x0, int y0) : tr(3) {
	// TODO:
	// 1) Не спавнить растянутые треугольники
	// 2) Не спавнить вырожденные треугольники (сделано)
	// 3) Не справнить за границами (вроде сделано, но как будто иногда все равно выходит)
	size_t radius = std::min({ 
		MaxRadius, 
		WindowWidth - x0, 
		(size_t)x0, 
		WindowHeight - y0, 
		(size_t)y0
	});

	size_t r = rand() % radius + MinRadius;
	float x1 = rand() % (2 * r + 1) + (x0 - r);
	float y1 = rand() % (2 * r + 1) + (y0 - r);
	float x2 = rand() % (2 * r + 1) + (x0 - r);
	float y2 = rand() % (2 * r + 1) + (y0 - r);
	
	// Если вторая точка спавнится на одной линии или там же где первая
	// Тогда перегенерируем пока точка не подойдет
	while ((x1 == y1) || (x2 == y2) || (x1 - x0) / (x2 - x1) == (y1 - y0) / (y2 - y1)) {
		x2 = rand() % (2 * r + 1) + (x0 - r);
		y2 = rand() % (2 * r + 1) + (y0 - r);
	}

	float x3 = 3 * x0 - x1 - x2;
	float y3 = 3 * y0 - y1 - y2;
	
	// TODO: Здесь, если третья вершина уходит за границу, то треугольник создается "пустой"
	// И не появляется на экране, поэтому надо сделать, чтобы всегда спавнился треугольник
	// Возможно, поменять как-то начальный алгоритм спавна точек
	if (IsPointInZone(x3, y3)) {
		tr.setPoint(0, { x1, y1 });
		tr.setPoint(1, { x2, y2 });
		tr.setPoint(2, { x3, y3 });
	}
}

Triangle::Triangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3) {
	tr.setPoint(0, { v1.x, v1.y });
	tr.setPoint(1, { v2.x, v2.y });
	tr.setPoint(2, { v3.x, v3.y });
	tr.setFillColor(sf::Color::Yellow);
	tr.setOutlineColor(sf::Color::Black);
	tr.setOutlineThickness(2);
}