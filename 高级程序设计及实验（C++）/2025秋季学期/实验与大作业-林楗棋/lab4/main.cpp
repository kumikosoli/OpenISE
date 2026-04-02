#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "ArcEdge.h"
#include "MyPolygon.h"
#include "Sector.h"
#include "StraightEgde.h"
#include "circle.h"

namespace {
constexpr double kPi = M_PI;

void DemoPrint() {
    const Point center(0.0, 0.0);
    const Point arcStart(1.0, 0.0);
    const Point arcEnd(0.0, 1.0);
    std::vector<Edge*> edges{new ArcEdge(arcStart, arcEnd, center), new StraightEdge(arcStart, arcEnd)};
    MyPolygon polygon(edges);

    std::cout << "示例打印：" << std::endl;
    polygon.Print();
}
} // namespace

TEST(StraightEdgeTest, LengthFollowsPythagorean) { //测试直线边长度计算
    const Point start(0.0, 0.0);
    const Point end(3.0, 4.0);
    StraightEdge edge(start, end);

    EXPECT_DOUBLE_EQ(5.0, edge.Length());
}

TEST(ShapeTest, CircleMetrics) { //测试圆的周长和面积计算
    const double radius = 2.0;
    Circle circle(Point(0.0, 0.0), radius);

    EXPECT_FLOAT_EQ(2.0 * kPi * radius, circle.Circumference());
    EXPECT_FLOAT_EQ(kPi * radius * radius, circle.Area());
}

TEST(ShapeTest, SectorMetrics) { //测试扇形的周长和面积计算
    const Point center(0.0, 0.0);
    const Point arcStart(1.0, 0.0);
    const Point arcEnd(0.0, 1.0);
    ArcEdge arc(arcStart, arcEnd, center);
    Sector sector(center, 1.0, arc);

    const double expectedCircumference = 2.0 + (kPi / 2.0);
    const double expectedArea = kPi / 4.0;

    EXPECT_FLOAT_EQ(expectedCircumference, sector.Circumference());
    EXPECT_FLOAT_EQ(expectedArea, sector.Area());
}

TEST(MyPolygonTest, ArcAndLineAreaMatchesSectorMinusTriangle) { //测试由一条弧边和一条直线边组成的多边形面积计算
    const Point center(0.0, 0.0);
    const Point arcStart(1.0, 0.0);
    const Point arcEnd(0.0, 1.0);
    const auto straight = new StraightEdge(arcStart, arcEnd);
    const auto arc = new ArcEdge(arcStart, arcEnd, center);

    std::vector<Edge*> edges{arc, straight};
    MyPolygon polygon(edges);

    const double expectedPerimeter = (kPi / 2.0) + std::sqrt(2.0);
    const double expectedArea = (kPi / 4.0) - 0.5;

    EXPECT_FLOAT_EQ(expectedPerimeter, polygon.Circumference());
    EXPECT_FLOAT_EQ(expectedArea, polygon.Area());
}

TEST(MyPolygonTest, TwoArcPolygonEqualsLensArea) { //测试由两条弧边组成的多边形面积计算
    const Point center1(0.0, 0.0);
    const Point center2(1.0, 0.0);
    const Point arc1Start(0.0, 1.0);
    const Point arc1End(0.0, -1.0);
    const Point arc2Start(1.0, 1.0);
    const Point arc2End(1.0, -1.0);

    auto* arc1 = new ArcEdge(arc1Start, arc1End, center1);
    auto* arc2 = new ArcEdge(arc2Start, arc2End, center2);
    std::vector<Edge*> edges{arc1, arc2};
    MyPolygon polygon(edges);

    const double expectedArea = (2.0 * kPi / 3.0) - (std::sqrt(3.0) / 2.0);
    const double expectedPerimeter = 2.0 * kPi;

    EXPECT_FLOAT_EQ(expectedArea, polygon.Area());
    EXPECT_FLOAT_EQ(expectedPerimeter, polygon.Circumference());
}

TEST(MyPolygonTest, ThreeStraightEdgePolygonArea) { //测试由三条直线边组成的多边形面积计算
    const Point p1(0.0, 0.0);
    const Point p2(4.0, 0.0);
    const Point p3(4.0, 3.0);

    auto* edge1 = new StraightEdge(p1, p2);
    auto* edge2 = new StraightEdge(p2, p3);
    auto* edge3 = new StraightEdge(p3, p1);
    std::vector<Edge*> edges{edge1, edge2, edge3};
    MyPolygon polygon(edges);

    const double expectedArea = 6.0;
    const double expectedPerimeter = 12.0;

    EXPECT_FLOAT_EQ(expectedArea, polygon.Area());
    EXPECT_FLOAT_EQ(expectedPerimeter, polygon.Circumference());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    const int result = RUN_ALL_TESTS();
    DemoPrint();
    return result;
}
