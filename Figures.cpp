#include "Figures.h"
#include <math.h>


double Distance(const point& a, const point& b) {
    return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}

point MassCenter(const std::vector<point>& points) {
    long double xsum = 0;
    long double ysum = 0;
    for (auto& pt : points) {
        xsum += pt.x;
        ysum += pt.y;
    }
    if (points.size() == 0)
        return {0, 0};
    else
        return {(int)(xsum / points.size()), (int) (ysum / points.size())};
}
