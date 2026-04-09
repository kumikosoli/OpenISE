#include "MyPolygon.h"
#include "ArcEdge.h"
#include "StraightEgde.h"
#include <cmath>
#include <iostream>

namespace {
double Distance(const Point& a, const Point& b) {
    const double dx = a.getX() - b.getX();
    const double dy = a.getY() - b.getY();
    return std::sqrt(dx * dx + dy * dy);
}
}
double Clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

MyPolygon::MyPolygon(const std::vector<Edge*>& edges) : edges_(edges) {}

MyPolygon::~MyPolygon() {
    for (Edge* edge : edges_) {
        delete edge;
    }
}

double MyPolygon::Circumference() const {
    double result = 0.0;
    for (const Edge* edge : edges_) {
        if (edge != nullptr) {
            result += edge->Length();
        }
    }
    return result;
}

double MyPolygon::Area() const {
    if (edges_.size() >= 3) {
        std::vector<Point> vertices;
        vertices.reserve(edges_.size() + 1);

        auto* firstStraight = dynamic_cast<StraightEdge*>(edges_.front());
        if (firstStraight == nullptr) {
            return UnknownValue;
        }
        vertices.push_back(firstStraight->get().first);

        for (Edge* edge : edges_) {
            auto* straight = dynamic_cast<StraightEdge*>(edge);
            if (straight == nullptr) {
                return UnknownValue;
            }
            vertices.push_back(straight->get().second);
        }

        double sum = 0.0;
        for (std::size_t i = 0; i + 1 < vertices.size(); ++i) {
            const Point& current = vertices[i];
            const Point& next = vertices[i + 1];
            sum += current.getX() * next.getY() - next.getX() * current.getY();
        }
        return std::fabs(sum) * 0.5;
    }

    if (edges_.size() != 2) {
        return UnknownValue;
    }

    int arcCount = 0;
    ArcEdge* arcA = nullptr;
    ArcEdge* arcB = nullptr;
    StraightEdge* line = nullptr;

    for (Edge* edge : edges_) {
        if (auto* arc = dynamic_cast<ArcEdge*>(edge)) {
            if (arcCount == 0) {
                arcA = arc;
            } else {
                arcB = arc;
            }
            ++arcCount;
        } else if (auto* straight = dynamic_cast<StraightEdge*>(edge)) {
            line = straight;
        }
    }

    if (arcCount == 1 && line != nullptr) {
        const auto endpoints = arcA->get();
        const Point& a = endpoints.first;
        const Point& b = endpoints.second;
        const Point& center = arcA->getCenter();
        const double radius = Distance(center, a);

        const double vx1 = a.getX() - center.getX();
        const double vy1 = a.getY() - center.getY();
        const double vx2 = b.getX() - center.getX();
        const double vy2 = b.getY() - center.getY();
        const double dot = vx1 * vx2 + vy1 * vy2;
        const double len1 = std::sqrt(vx1 * vx1 + vy1 * vy1);
        const double len2 = std::sqrt(vx2 * vx2 + vy2 * vy2);
        double angle = std::acos(Clamp(dot / (len1 * len2), -1.0, 1.0));

        const double sectorArea = 0.5 * radius * radius * angle;
        const double triangleArea = 0.5 * radius * radius * std::sin(angle);
        return std::fabs(sectorArea - triangleArea);
    }

    if (arcCount == 2) {
        const Point& c1 = arcA->getCenter();
        const Point& c2 = arcB->getCenter();
        const auto endpointsA = arcA->get();
        const auto endpointsB = arcB->get();
        const double r1 = Distance(c1, endpointsA.first);
        const double r2 = Distance(c2, endpointsB.first);
        const double d = Distance(c1, c2);

        if (d >= r1 + r2 || d <= std::fabs(r1 - r2)) {
            return UnknownValue;
        }

        const double alpha = 2.0 * std::acos(Clamp((r1 * r1 + d * d - r2 * r2) / (2.0 * r1 * d), -1.0, 1.0));
        const double beta = 2.0 * std::acos(Clamp((r2 * r2 + d * d - r1 * r1) / (2.0 * r2 * d), -1.0, 1.0));

        const double area1 = 0.5 * r1 * r1 * (alpha - std::sin(alpha));
        const double area2 = 0.5 * r2 * r2 * (beta - std::sin(beta));
        return area1 + area2;
    }

    return UnknownValue;
}

void MyPolygon::Print() const {
    std::cout << "多边形由" << edges_.size() << "条边组成：" << std::endl;
    for (const Edge* edge : edges_) {
        if (edge != nullptr) {
            edge->Print();
        }
    }
    std::cout << "周长：" << Circumference() << std::endl;
    std::cout << "面积：" << Area() << std::endl;
}
