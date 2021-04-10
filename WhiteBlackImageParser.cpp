#include "WhiteBlackImageParser.h"
#include <algorithm>


bool IsBlack(bool pixel) {
    return pixel;
}


bool DifferentVertexes(const point& a, const point& b) {
    return Distance(a, b) < CONSTANT_DIFFERENT_VERTEXIES;
}

bool ConnectedBlackLine(const WhiteBlackImage& image, point a, point b) {
    //To do
}

bool SameVertex(point a, point b) {
    return Distance(a, b) < 40; //To do
}

std::pair<double, double> GetRectangleParams(std::vector<point> vertexes) {
    auto compare = [start_vertex = vertexes[0]](const point& left, const point& right) -> bool {
        return Distance(left, start_vertex) < Distance(right, start_vertex);
    };
    std::sort(vertexes.begin(), vertexes.end(), compare);
    return {Distance(vertexes[0], vertexes[1]), Distance(vertexes[0], vertexes[2])};
}


AnswerForQuestion FigureParams(const ImageWithParams& image_pack) {
    size_t width = std::get<2>(image_pack);
    size_t height = std::get<1>(image_pack);
    WhiteBlackImage image = std::get<0>(image_pack);
    std::vector<point> black_points;
    for (int y =0; y<height; y++) {
        for (int x=0; x<width; x++)
            if (IsBlack(image[y][x])) {
                black_points.push_back({y, x});
            }
    }
    point center = MassCenter(black_points);
    std::vector<point> vertexes;
    const size_t MAX_NEEDED_VERTEXES = 5;
    auto compare = [center](const point& left, const point& right) -> bool {
        return Distance(left, center) > Distance(right, center);
    };
    std::sort(black_points.begin(), black_points.end(), compare);

    const int DistanceDifference = 8;
    for (auto& point : black_points)
        if (vertexes.size() < MAX_NEEDED_VERTEXES) {
            if (abs(Distance(point, center) - Distance(black_points.front(), center)) < DistanceDifference) {
                bool good = true;
                for (auto vertex : vertexes)
                    if (SameVertex(vertex, point)) {
                        good = false;
                    }
                if (good) {
                    vertexes.push_back(point);
                }
            }
        }
    if (vertexes.size() >= 5) {
        return AnswerForQuestion("This is a circle with radius " + std::to_string(Distance(center, vertexes.back())));
    }
    if (vertexes.size() == 4) {
        const double DIFFERENCE_BETWEEN_RECTANGLE_AND_SQUARE = 5;
        auto [width, height] = GetRectangleParams(vertexes);
        std::string Answer = "This is a ";
        if (abs(width - height) < DIFFERENCE_BETWEEN_RECTANGLE_AND_SQUARE) {
            Answer += "square with side length " + std::to_string(width);
        } else {
            Answer += "rectangle with sides length " + std::to_string(width) + " and ";
            Answer += std::to_string(height);
        }
        return Answer;
    }
    if (vertexes.size() <= 3) {
        std::string Answer = "This is triangle"; // To do
        return Answer;
    }
}
