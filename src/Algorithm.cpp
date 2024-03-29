#include "Algorithm.h"
#include "Figures.h"
#include <iostream>

float aFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.y - v2.y;
}

float bFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v2.x - v1.x;
}

float cFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x * v2.y - v2.x * v1.y;
}

sf::Vector2f IntersectionPoint(float a1, float b1, float c1, float a2, float b2, float c2) {
    float intersectX = c1 * (b1 - b2) / (a1 * b2 - a2 * b1);
    float intersectY = c1 * (a2 - a1) / (a1 * b2 - a2 * b1);
    sf::Vector2f intersect_point = { intersectX, intersectY };

    return intersect_point;
}

bool PointChecking(float a, float b, float c, const sf::Vector2f& v1, const sf::Vector2f& v2) {
    if ((a * v1.x + b * v1.y + c) * (a * v2.x + b * v2.y + c) <= 0) {
        return true;
    }
    return false;
}

bool AreaChecking(float a, float b, float c, const sf::Vector2f& v, const sf::Vector2f& v3) {
    if ((a * v.x + b * v.y + c) * (a * v3.x + b * v3.y + c) >= 0) {
        return true;
    }
    return false;
}

figures::Polygon IntersectionArea(const figures::Polygon& polygon, float a, float b, float c, const sf::Vector2f& v3) {
    int ind1 = -1, ind2 = -1;
    sf::Vector2f interpoint1, interpoint2, v1, v2;
    std::vector<sf::Vector2f> result_vertices;
    size_t result_point_count = 0;
    size_t point_count = polygon.getPointCount();

    for (size_t i = 0; i != point_count; ++i) {
        v1 = polygon.getPoint(i);
        v2 = polygon.getPoint((i + 1) % point_count);
        if (PointChecking(a, b, c, v1, v2)) {
            if (ind1 == -1) {
                ind1 = i;
                interpoint1 = IntersectionPoint(a, b, c, aFind(v1, v2), bFind(v1, v2), cFind(v1, v2));
            }
            else {
                ind2 = i;
                interpoint2 = IntersectionPoint(a, b, c, aFind(v1, v2), bFind(v1, v2), cFind(v1, v2));
                break;
            }
        }
    }

    if ((ind1 == -1) && (AreaChecking(a, b, c, v1, v3))) {
        result_point_count = point_count;
        for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
    }

    // НЕ ВСЕ СЛУЧАИ ОБРАБОТАНЫ, когда точка пересечения совпадает с вершиной????? 
    else if ((ind2 != -1) && (ind1 != -1)) {
        if (interpoint1 == interpoint2) {
            if (AreaChecking(a, b, c, interpoint1, v3)) {
                result_point_count = point_count;
                for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
            }
            else {
                result_point_count = 1;
                result_vertices.push_back(interpoint1);
            }
        }
        else if (AreaChecking(a, b, c, polygon.getPoint(ind2), v3)) {
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
    float a, b, c;
    figures::Polygon resultPolygon = inter_polygon;
    size_t point_count = polygon.getPointCount();

    for (size_t i = 0; i != point_count; ++i) {
        v1 = polygon.getPoint(i);
        v2 = polygon.getPoint((i + 1) % point_count);
        v3 = polygon.getPoint((i + 2) % point_count);
        a = aFind(v1, v2);
        b = bFind(v1, v2);
        c = cFind(v1, v2);
        resultPolygon = IntersectionArea(resultPolygon, a, b, c, v3);
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
