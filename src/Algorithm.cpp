#include "Algorithm.h"
#include "Figures.h"
#include <iostream>

float kFind(sf::Vector2f v1, sf::Vector2f v2) return (v1.y - v2.y) / (v1.x - v2.x);

float bFind(sf::Vector2f v1, sf::Vector2f v2) return (v1.x * v2.y - v2.x * v1.y) / (v1.x - v2.x);

sf::Vector2f IntersectionPoint(float k1, float b1, float k2, float b2) {
    float intersectX = -(b1 - b2) / (k1 - k2);
    float intersectY = k1 * intersectX + b1;
    sf::Vector2f intersect_point = { intersectX, intersectY };

    return intersect_point;
}

bool AreaCheckingPoint(float k, float b, sf::Vector2f v1, sf::Vector2f v2) {
    if ((v1.y - k * v1.x - b) * (v2.y - k * v2.x - b) >= 0) {
        return true;
    }
    return false;
}

Polygon IntersectionPolygon(Polygon polygon, float k, float b, sf::Vector2f v3) {
    size_t ind1 = -1, ind2 = -1;
    sf::Vector2f interpoint1, interpoint2, v1, v2;
    std::vector<sf::Vector2f> result_vertices(0);
    size_t result_point_count = 0;

    for (size_t i = 0; i != polygon.getPointCount(); ++i) {
        v1 = polygon.getPoint(i);
        v2 = polygon.getPoint(i + 1);
        if (not AreaCheckingPoint(k, b, v1, v2)) {
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
    if ((ind1 == -1 or ind2 == -1) and (not AreaCheckingPoint(k, b, v1, v2))) {
        if (ind1 == -1) {
            ind1 = polygon.getPointCount() - 1;
            interpoint1 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
        }
        else {
            ind2 = polygon.getPointCount() - 1;
            interpoint2 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
        }
    }

    if ((ind1 == -1) and AreaCheckingPoint(k, b, v1, v3)) {
        result_point_count = polygon.getPointCount();
        for (size_t i == 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
    }

    else if (ind2 == -1) {
        if (AreaCheckingPoint(k, b, interpoint1, v3)) {
            result_point_count = polygon.getPointCount();
            for (size_t i == 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
        }
        else {
            result_point_count = 1;
            result_vertices.push_back(interpoint1);
        }
    }

    // НЕ ВСЕ СЛУЧАИ ОБРАБОТАНЫ, когда точка пересечения совпадает с вершиной????? 
    else {
        if (AreaCheckingPoint(k, b, polygon.getPoint(ind2), v3)) {
            result_vertices.push_back(interpoint1);
            for (size_t i = ind1 + 1; ind2 + 1; i++) result_vertices.push_back(polygon.getPoint(i));
            result_vertices.push_back(interpoint2);
            result_point_count = ind2 - ind1 + 2;
        }
        else {
            result_vertices.push_back(interpoint1);
            result_vertices.push_back(interpoint2);
            for (size_t i = ind2 + 1; polygon.getPointCount() + ind1 + 1; i++) result_vertices.push_back(polygon.getPoint(i % polygon.getPointCount()));
            result_point_count = polygon.getPointCount() - (ind2 - ind1) + 2;
        }
    }

    Polygon result_polygon = { result_point_count, result_vertices };
    return result_polygon;
}