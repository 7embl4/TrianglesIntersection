#include "Algorithm.h"
#include "Figures.h"
#include <iostream>

float kFind(sf::Vector2f v1, sf::Vector2f v2) {
    return (v1.y - v2.y) / (v1.x - v2.x);
}

float bFind(sf::Vector2f v1, sf::Vector2f v2) {
    return (v1.x * v2.y - v2.x * v1.y) / (v1.x - v2.x);
}

sf::Vector2f IntersectionPoint(float k1, float b1, float k2, float b2) {
    float intersectX = -(b1 - b2) / (k1 - k2);
    float intersectY = k1 * intersectX + b1;
    sf::Vector2f intersect_point = { intersectX, intersectY };

    return intersect_point;
}

bool PointChecking(float& k, float& b, const sf::Vector2f& v1, const sf::Vector2f& v2) {
    if ((v1.y - k * v1.x - b) * (v2.y - k * v2.x - b) <= 0) {
        return true;
    }
    return false;
}

bool AreaChecking(float& k, float& b, const sf::Vector2f& v, const sf::Vector2f& v3) {
    if ((v.y - k * v.x - b) * (v3.y - k * v3.x - b) >= 0) {
        return true;
    }
    return false;
}

Polygon IntersectionArea(const Polygon& polygon, float& k, float& b, const sf::Vector2f& v3) {
    int ind1 = -1, ind2 = -1;
    sf::Vector2f interpoint1, interpoint2, v1, v2;
    std::vector<sf::Vector2f> result_vertices;
    size_t result_point_count = 0;

    for (size_t i = 0; i != polygon.getPointCount() - 1; ++i) {
        v1 = polygon.getPoint(i);
        v2 = polygon.getPoint(i + 1);
        if (PointChecking(k, b, v1, v2)) {
            if (ind1 == -1) {
                ind1 = i;
                interpoint1 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
            }
            else {
                ind2 = i;
                interpoint2 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
                break;
            }
        }
    }

    //Последняя линия
    v1 = polygon.getPoint(0);
    v2 = polygon.getPoint(polygon.getPointCount() - 1);
    if ((ind1 == -1 || ind2 == -1) && (PointChecking(k, b, v1, v2))) {
        if (ind1 == -1) {
            ind1 = polygon.getPointCount() - 1;
            interpoint1 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
        }
        else {
            ind2 = polygon.getPointCount() - 1;
            interpoint2 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
        }
    }

    if ((ind1 == -1) && (AreaChecking(k, b, v1, v3))) {
        result_point_count = polygon.getPointCount();
        for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
    }

    else if (ind2 == -1) {
        if (AreaChecking(k, b, interpoint1, v3)) {
            result_point_count = polygon.getPointCount();
            for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
        }
        else {
            result_point_count = 1;
            result_vertices.push_back(interpoint1);
        }
    }

    // НЕ ВСЕ СЛУЧАИ ОБРАБОТАНЫ, когда точка пересечения совпадает с вершиной????? 
    else {
        if (AreaChecking(k, b, polygon.getPoint(ind2), v3)) {
            result_vertices.push_back(interpoint1);
            for (size_t i = ind1 + 1; i != ind2 + 1; ++i) result_vertices.push_back(polygon.getPoint(i));
            result_vertices.push_back(interpoint2);
            result_point_count = ind2 - ind1 + 2;
        }
        else {
            result_vertices.push_back(interpoint1);
            result_vertices.push_back(interpoint2);
            for (size_t i = ind2 + 1; i != polygon.getPointCount() + ind1 + 1; ++i) result_vertices.push_back(polygon.getPoint(i % polygon.getPointCount()));
            result_point_count = polygon.getPointCount() - (ind2 - ind1) + 2;
        }
    }

    return Polygon(result_point_count, result_vertices);
}

Polygon IntersectionPolygon(const Triangle& triangle, const Polygon& polygon) {
    sf::Vector2f v1 = triangle.getPoint(0);
    sf::Vector2f v2 = triangle.getPoint(1);
    sf::Vector2f v3 = triangle.getPoint(2);

    float k1 = kFind(v1, v2), b1 = bFind(v1, v2);
    float k2 = kFind(v2, v3), b2 = bFind(v2, v3);
    float k3 = kFind(v3, v1), b3 = bFind(v3, v1);

    return IntersectionArea(IntersectionArea(IntersectionArea(polygon, k1, b1, v3), k2, b2, v1), k3, b3, v2);
}

Polygon CommonIntersection(const std::vector<Triangle>& triangles, size_t& count) {
    Polygon polygon{ triangles[0] };

    for (size_t i = 1; i != count; ++i) {
        polygon = IntersectionPolygon(triangles[i], polygon);
    }

    return polygon;
}
