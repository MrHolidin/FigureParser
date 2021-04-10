#pragma once
#include <vector>

enum Figures {
    Circle,
    Rectangle,
    Triangle,
    Square
};

struct point {
    int x;
    int y;
};

point MassCenter(const std::vector<point>& points);

double Distance(const point& a, const point& b);