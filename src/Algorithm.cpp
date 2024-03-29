#include "Algorithm.h"
#include "Figures.h"
#include <iostream>

float kFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.y - v2.y) / (v1.x - v2.x);
}

float bFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x * v2.y - v2.x * v1.y) / (v1.x - v2.x);
}

sf::Vector2f IntersectionPoint(float k1, float b1, float k2, float b2) {
    float intersectX = -(b1 - b2) / (k1 - k2);
    float intersectY = k1 * intersectX + b1;
    sf::Vector2f intersect_point = { intersectX, intersectY };

    return intersect_point;
}

bool PointChecking(float k, float b, const sf::Vector2f& v1, const sf::Vector2f& v2) {
    if ((v1.y - k * v1.x - b) * (v2.y - k * v2.x - b) <= 0) {
        return true;
    }
    return false;
}

bool AreaChecking(float k, float b, const sf::Vector2f& v, const sf::Vector2f& v3) {
    if ((v.y - k * v.x - b) * (v3.y - k * v3.x - b) >= 0) {
        return true;
    }
    return false;
}

figures::Polygon IntersectionArea(const figures::Polygon& polygon, float k, float b, const sf::Vector2f& v3) {
    int ind1 = -1, ind2 = -1;
    sf::Vector2f interpoint1, interpoint2, v1, v2;
    std::vector<sf::Vector2f> result_vertices;
    size_t result_point_count = 0;
    size_t point_count = polygon.getPointCount();

    for (size_t i = 0; i != point_count; ++i) {
        v1 = polygon.getPoint(i);
        v2 = polygon.getPoint((i + 1) % point_count);
        if (PointChecking(k, b, v1, v2)) {
            if (ind1 == -1) {
                ind1 = i;
                interpoint1 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
                //if ((v1.y - k * v1.x - b) * (v2.y - k * v2.x - b) == 0) break;
            }
            else {
                ind2 = i;
                interpoint2 = IntersectionPoint(k, b, kFind(v1, v2), bFind(v1, v2));
                break;
            }
        }
    }

    if ((ind1 == -1) && (AreaChecking(k, b, v1, v3))) {
        result_point_count = point_count;
        for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
    }

    else if ((ind2 == -1) && (ind1 != -1)) {
        if (AreaChecking(k, b, interpoint1, v3)) {
            result_point_count = point_count;
            for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
        }
        else {
            result_point_count = 1;
            result_vertices.push_back(interpoint1);
        }
    }

    // НЕ ВСЕ СЛУЧАИ ОБРАБОТАНЫ, когда точка пересечения совпадает с вершиной????? 
    else if ((ind2 != -1) && (ind1 != -1)) {
        if (AreaChecking(k, b, polygon.getPoint(ind2), v3)) {
            result_vertices.push_back(interpoint1);
            for (size_t i = ind1 + 1; i != ind2 + 1; ++i) result_vertices.push_back(polygon.getPoint(i));
            result_vertices.push_back(interpoint2);
            result_point_count = ind2 - ind1 + 2;
        }
        else {
            result_vertices.push_back(interpoint1);
            result_vertices.push_back(interpoint2);
            for (size_t i = ind2 + 1; i != point_count + ind1 + 1; ++i) result_vertices.push_back(polygon.getPoint(i % point_count));
            result_point_count = point_count - (ind2 - ind1) + 2;
        }
    }

    return figures::Polygon(result_point_count, result_vertices);
}

figures::Polygon IntersectionPolygon(const figures::Polygon& polygon, const figures::Polygon& inter_polygon) {
    sf::Vector2f v1, v2, v3;
    float k, b;
    figures::Polygon resultPolygon = inter_polygon;
    size_t point_count = polygon.getPointCount();

    for (size_t i = 0; i != point_count; ++i) {
        v1 = polygon.getPoint(i);
        v2 = polygon.getPoint((i + 1) % point_count);
        v3 = polygon.getPoint((i + 2) % point_count);
        k = kFind(v1, v2);
        b = bFind(v1, v2);
        resultPolygon = IntersectionArea(resultPolygon, k, b, v3);
    }

    return resultPolygon;
}

figures::Polygon CommonIntersection(const std::vector<figures::Polygon>& polygons, size_t count) {
    figures::Polygon polygon = polygons[0];

    for (size_t i = 1; i != count; ++i) {
        polygon = IntersectionPolygon(polygons[i], polygon);
    }

    return polygon;
}
