#include "Algorithm.h"
#include "Figures.h"
#include <iostream>

float aFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.y - v2.y);
}

float bFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v2.x - v1.x;
}

float cFind(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x * v2.y - v2.x * v1.y;
}

sf::Vector2f IntersectionPoint(float a1, float b1, float c1, float a2, float b2, float c2) {
    float intersectX = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    float intersectY = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);

    return sf::Vector2f(intersectX, intersectY);
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
    size_t dop = 0;

    if ((point_count == 1) && (AreaChecking(a, b, c, polygon.getPoint(0), v3))) {
        result_point_count = 1;
        result_vertices.push_back(polygon.getPoint(0));
    }

    //Последняя линия
    else if (point_count > 1) {
        for (size_t i = 0; i != point_count; ++i) {
            v1 = polygon.getPoint(i);
            v2 = polygon.getPoint((i + 1) % point_count);
            if (PointChecking(a, b, c, v1, v2)) {
                if (ind1 == -1) {
                    ind1 = i;
                    if (a * bFind(v1, v2) - aFind(v1, v2) * b == 0) {
                        interpoint1 = v1;
                        interpoint2 = v2;
                        dop = 7;
                        break;
                    }
                    else interpoint1 = IntersectionPoint(a, b, c, aFind(v1, v2), bFind(v1, v2), cFind(v1, v2));
                }
                else {
                    ind2 = i;
                    if (a * bFind(v1, v2) - aFind(v1, v2) * b == 0) {
                        interpoint2 = v2;
                    }
                    else interpoint2 = IntersectionPoint(a, b, c, aFind(v1, v2), bFind(v1, v2), cFind(v1, v2));
                    break;
                }
            }
        }
        if ((ind1 == -1) && (AreaChecking(a, b, c, v1, v3))) {
            result_point_count = point_count;
            for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
        }

    

        if ((ind1 == -1) && (AreaChecking(a, b, c, v1, v3))) {
            result_point_count = point_count;
            for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
        }
        if ((ind2 == -1) && (ind1 != -1)) {
            if (dop == 7) {
                result_point_count = 2;
                result_vertices.push_back(interpoint1);
                result_vertices.push_back(interpoint2);
            }
            else {
                result_point_count = 1;
                result_vertices.push_back(interpoint1);
            }
        }
        else if ((ind2 != -1) && (ind1 != -1)) {
            if (interpoint1 == interpoint2) {
                if (point_count == 2) {
                    result_point_count = 2;
                    result_vertices.push_back(interpoint1);
                    if (AreaChecking(a, b, c, polygon.getPoint(0), v3)) result_vertices.push_back(polygon.getPoint(0));
                    else result_vertices.push_back(polygon.getPoint(1));
                }
                else if (AreaChecking(a, b, c, polygon.getPoint((ind1 + 1) % point_count), v3)) {
                    result_point_count = point_count;
                    for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
                }
                else {
                    result_point_count = 1;
                    result_vertices.push_back(interpoint1);
                }
            }
            else if ((interpoint1 == v1) && (interpoint2 == v2)) {
                if (AreaChecking(a, b, c, polygon.getPoint((ind2 + 2) % point_count), v3)) {
                    result_point_count = point_count;
                    for (size_t i = 0; i != result_point_count; ++i) result_vertices.push_back(polygon.getPoint(i));
                }
                else {
                    result_point_count = 2;
                    result_vertices.push_back(interpoint1);
                    result_vertices.push_back(interpoint2);
                }
            }
            else if (AreaChecking(a, b, c, polygon.getPoint(ind2), v3)) {
                result_vertices.push_back(interpoint1);
                for (size_t i = ind1 + 1; i != ind2 + 1; ++i) {
                    if ((polygon.getPoint(i) == interpoint1) || (polygon.getPoint(i) == interpoint2)) {
                        dop += 1;
                    }
                    result_vertices.push_back(polygon.getPoint(i));
                }
                result_vertices.push_back(interpoint2);
                result_point_count = ind2 - ind1 + 2 - dop;
            }
            else {
                result_vertices.push_back(interpoint1);
                result_vertices.push_back(interpoint2);
                for (size_t i = ind2 + 1; i != point_count + ind1 + 1; ++i) {
                    if ((polygon.getPoint(i % point_count) == interpoint1) || (polygon.getPoint(i % point_count) == interpoint2)) {
                        dop += 1;
                    }
                    result_vertices.push_back(polygon.getPoint(i % point_count));
                }
                result_point_count = point_count - (ind2 - ind1) + 2 - dop;
            }
        }
    }

    return figures::Polygon(result_point_count, result_vertices);
}

figures::Polygon IntersectionPolygon(const figures::Triangle& triangle, const figures::Polygon& polygon) {
    sf::Vector2f v1, v2, v3;
    float a, b, c;
    figures::Polygon resultPolygon = polygon;

    for (size_t i = 0; i != 3; ++i) {
        v1 = triangle.getPoint(i);
        v2 = triangle.getPoint((i + 1) % 3);
        v3 = triangle.getPoint((i + 2) % 3);
        a = aFind(v1, v2);
        b = bFind(v1, v2);
        c = cFind(v1, v2);
        resultPolygon = IntersectionArea(resultPolygon, a, b, c, v3);
    }

    return resultPolygon;
}

figures::Polygon CommonIntersection(const std::vector<figures::Triangle>& triangles, size_t count) {
    figures::Polygon polygon{ triangles[0] };

    for (size_t i = 1; i != count; ++i) {
        polygon = IntersectionPolygon(triangles[i], polygon);
    }

    return polygon;
}
