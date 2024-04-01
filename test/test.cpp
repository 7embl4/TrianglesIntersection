#include <iostream>
#include <Windows.h>
#include <gtest/gtest.h>
#include "Figures.h"
#include "Algorithm.h"

TEST(TriangleIntersection_Test1, Just_Intersection1_2_Triangles) {
	figures::Triangle triangle1(sf::Vector2f(0, 2), sf::Vector2f(3, -1), sf::Vector2f(1, -3));
	figures::Triangle triangle2(sf::Vector2f(4, 0), sf::Vector2f(-1, -1), sf::Vector2f(0, 1));

	figures::Polygon polygon1(triangle1);
	figures::Polygon polygon2(triangle2);

	std::vector<figures::Triangle> triangles = { triangle1, triangle2 };

	figures::Polygon result(CommonIntersection(triangles, 2));


	//output of coordinates
	int i = 0;
	for (i; i < result.getPointCount(); i++) {
		std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
	}
}

TEST(TriangleIntersection_Test2, Point_Intersection) {
	figures::Triangle triangle1(sf::Vector2f(2, -2), sf::Vector2f(5, 1), sf::Vector2f(4, -2));
	figures::Triangle triangle2(sf::Vector2f(-1, -1), sf::Vector2f(0, 1), sf::Vector2f(4, 0));

	figures::Polygon polygon1(triangle1);
	figures::Polygon polygon2(triangle2);

	std::vector<figures::Triangle> triangles = { triangle1, triangle2 };

	figures::Polygon result(CommonIntersection(triangles, 2));

	//output of coordinates
	int i = 0;
	for (i; i < result.getPointCount(); i++) {
		std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
	}
}

TEST(TriangleIntersection_Test3, Line_Intersection) {
	figures::Triangle triangle1(sf::Vector2f(2, -2), sf::Vector2f(5, 1), sf::Vector2f(4, -2));
	figures::Triangle triangle2(sf::Vector2f(1, -2), sf::Vector2f(5, -2), sf::Vector2f(3, -3));

	figures::Polygon polygon1(triangle1);
	figures::Polygon polygon2(triangle2);

	std::vector<figures::Triangle> triangles = { triangle1, triangle2 };

	figures::Polygon result(CommonIntersection(triangles, 2));

	//output of coordinates
	int i = 0;
	for (i; i < result.getPointCount(); i++) {
		std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
	}
}

TEST(TriangleIntersection_Test4, Empty) {
	figures::Triangle triangle1(sf::Vector2f(0, 1), sf::Vector2f(2, 2), sf::Vector2f(3, 0));
	figures::Triangle triangle2(sf::Vector2f(1, -2), sf::Vector2f(5, -2), sf::Vector2f(3, -3));

	figures::Polygon polygon1(triangle1);
	figures::Polygon polygon2(triangle2);

	std::vector<figures::Triangle> triangles = { triangle1, triangle2 };

	figures::Polygon result(CommonIntersection(triangles, 2));

	//output of coordinates
	int i = 0;
	for (i; i < result.getPointCount(); i++) {
		std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
	}
}

TEST(TriangleIntersection_Test5, triangle_in_triangle) {
	figures::Triangle triangle1(sf::Vector2f(-4, -2), sf::Vector2f(2, 2), sf::Vector2f(3, -5));
	figures::Triangle triangle2(sf::Vector2f(-1, -2), sf::Vector2f(1, -1), sf::Vector2f(2, -2));

	figures::Polygon polygon1(triangle1);
	figures::Polygon polygon2(triangle2);

	std::vector<figures::Triangle> triangles = { triangle1, triangle2 };

	figures::Polygon result(CommonIntersection(triangles, 2));


	//output of coordinates
	int i = 0;
	for (i; i < result.getPointCount(); i++) {
		std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
	}
}

TEST(TriangleIntersection_Test6, justIntersection2_4_Triangles) {
	figures::Triangle triangle1(sf::Vector2f(-2, -2), sf::Vector2f(0, 4), sf::Vector2f(12, -2));
	figures::Triangle triangle2(sf::Vector2f(0, -4), sf::Vector2f(4, 6), sf::Vector2f(10, -4));
	figures::Triangle triangle3(sf::Vector2f(0, -2), sf::Vector2f(12, 2), sf::Vector2f(14, 0));
	figures::Triangle triangle4(sf::Vector2f(0, -6), sf::Vector2f(8, 4), sf::Vector2f(6, -6));

	figures::Polygon polygon1(triangle1);
	figures::Polygon polygon2(triangle2);
	figures::Polygon polygon3(triangle3);
	figures::Polygon polygon4(triangle4);

	std::vector<figures::Triangle> triangles = { triangle1, triangle2, triangle3, triangle4 };

	figures::Polygon result(CommonIntersection(triangles, 4));

	//output of coordinates
	int i = 0;
	for (i; i < result.getPointCount(); i++) {
		std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
	}
}

