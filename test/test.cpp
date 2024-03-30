#include <iostream>
#include <Windows.h>
#include <gtest/gtest.h>
#include "Figures.h"
#include "Algorithm.h"

TEST(CommonIntersectionTest1, Just_Intersection1) {
    //create polygons
    figures::Polygon polygon1(4, { sf::Vector2f(-2, 0), sf::Vector2f(-2, 2), sf::Vector2f(0, 0), sf::Vector2f(0, 2) });
    figures::Polygon polygon2(4, { sf::Vector2f(-3, -2), sf::Vector2f(-3, 2), sf::Vector2f(1, 2), sf::Vector2f(1, -2) });
    size_t expectedCount = 4;

    //vector with polygons for function
    std::vector<figures::Polygon> polygons = { polygon1, polygon2 };
    figures::Polygon result(CommonIntersection(polygons, 2));

    //output of coordinates
    int i = 0;
    for (i; i < result.getPointCount(); i++) {
        std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
    }
}

TEST(CommonIntersectionTest2, hexagon) {
    //create polygons
    figures::Polygon polygon1(4, { sf::Vector2f(2, 3), sf::Vector2f(5, 4), sf::Vector2f(7, 2), sf::Vector2f(3, 0) });
    figures::Polygon polygon2(4, { sf::Vector2f(1, 1), sf::Vector2f(3, 3), sf::Vector2f(5, 2), sf::Vector2f(4, 0) });
    size_t expectedCount = 6;

    //vector with polygons for function
    std::vector<figures::Polygon> polygons = { polygon1, polygon2 };
    figures::Polygon result(CommonIntersection(polygons, 2));

    //output of coordinates
    int i = 0;
    for (i; i < result.getPointCount(); i++) {
        std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
    }
}

TEST(CommonIntersectionTest3, empty) {
    //create polygons
    figures::Polygon polygon1(4, { sf::Vector2f(-2, 0), sf::Vector2f(-2, 2), sf::Vector2f(0, 2), sf::Vector2f(0, 0) });
    figures::Polygon polygon2(4, { sf::Vector2f(1, 0), sf::Vector2f(1, 1), sf::Vector2f(2, 2), sf::Vector2f(2, 1) });
    size_t expectedCount = 0;

    //vector with polygons for function
    std::vector<figures::Polygon> polygons = { polygon1, polygon2 };
    figures::Polygon result(CommonIntersection(polygons, 2));

    //output of coordinates
    int i = 0;
    for (i; i < result.getPointCount(); i++) {
        std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
    }
}

TEST(CommonIntersectionTest4, pentagon) {
    //create polygons
    figures::Polygon polygon1(4, { sf::Vector2f(2, 3), sf::Vector2f(5, 4), sf::Vector2f(7, 2), sf::Vector2f(3, 0) });
    figures::Polygon polygon2(4, { sf::Vector2f(1, 1), sf::Vector2f(3, 3), sf::Vector2f(5, 2), sf::Vector2f(4, 0) });
    figures::Polygon polygon3(5, { sf::Vector2f(0, -1), sf::Vector2f(1, 2), sf::Vector2f(6, 1), sf::Vector2f(4, -1), sf::Vector2f(2, -2) });
    size_t expectedCount = 5;

    //vector with polygons for function
    std::vector<figures::Polygon> polygons = { polygon1, polygon2, polygon3 };
    figures::Polygon result(CommonIntersection(polygons, 3));

    //output of coordinates
    int i = 0;
    for (i; i < result.getPointCount(); i++) {
        std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
    }
}

TEST(CommonIntersectionTest5, line_Intersection) {
    //create polygons
    figures::Polygon polygon1(4, { sf::Vector2f(-4, -2), sf::Vector2f(-2, 2), sf::Vector2f(1, -3), sf::Vector2f(-1, -4) });
    figures::Polygon polygon2(4, { sf::Vector2f(-3, -5), sf::Vector2f(3, -2), sf::Vector2f(5, -5), sf::Vector2f(3, -7) });
    size_t expectedCount = 2;

    //vector with polygons for function
    std::vector<figures::Polygon> polygons = { polygon1, polygon2 };
    figures::Polygon result(CommonIntersection(polygons, 2));

    //output of coordinates
    int i = 0;
    for (i; i < result.getPointCount(); i++) {
        std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
    }

}

TEST(CommonIntersectionTest6, point_intersection) {
    //create polygons
    figures::Polygon polygon1(4, { sf::Vector2f(1, 1), sf::Vector2f(6, 1), sf::Vector2f(5, -1), sf::Vector2f(3, -2) });
    figures::Polygon polygon2(4, { sf::Vector2f(-3, -5), sf::Vector2f(3, -2), sf::Vector2f(5, -5), sf::Vector2f(3, -7) });
    size_t expectedCount = 1;

    //vector with polygons for function
    std::vector<figures::Polygon> polygons = { polygon1, polygon2 };
    figures::Polygon result(CommonIntersection(polygons, 2));

    //output of coordinates
    int i = 0;
    for (i; i < result.getPointCount(); i++) {
        std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
    }
}

TEST(CommonIntersectionTest7, intersection_9_vertices) {
    //create polygons
    figures::Polygon polygon1(8, { sf::Vector2f(-4, 1), sf::Vector2f(-3, 3), sf::Vector2f(-2, 4), sf::Vector2f(0, 3),
        sf::Vector2f(2, 4), sf::Vector2f(4, 2), sf::Vector2f(1, -1), sf::Vector2f(-2, -1)
        });
    figures::Polygon polygon2(5, { sf::Vector2f(-4, -2), sf::Vector2f(-1, 4), sf::Vector2f(4, 3), sf::Vector2f(3, 0), sf::Vector2f(-1, -2) });
    size_t expectedCount = 9;

    //vector with polygons for function
    std::vector<figures::Polygon> polygons = { polygon1, polygon2 };
    figures::Polygon result(CommonIntersection(polygons, 2));

    //output of coordinates
    int i = 0;
    for (i; i < result.getPointCount(); i++) {
        std::cout << result.getPoint(i).x << "  " << result.getPoint(i).y << "\n";
    }

}