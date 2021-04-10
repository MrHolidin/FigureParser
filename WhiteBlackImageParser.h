#pragma once
#include "Figures.h"
#include "png_converting.h"
#include <string>
#include <vector>
#include <iostream>


struct AnswerForQuestion {
    AnswerForQuestion(std::string s) : answer_(s) {

    }
    void Write(std::ostream& os) {
        os << answer_ << std::endl;
    }
private:
    std::string answer_;

};


bool IsBlack(bool pixel);

const int CONSTANT_DIFFERENT_VERTEXIES = 10;

bool DifferentVertexes(const point& a, const point& b);

bool ConnectedBlackLine(const WhiteBlackImage& image, point a, point b);

bool SameVertex(point a, point b);

std::pair<double, double> GetRectangleParams(std::vector<point> vertexes);

AnswerForQuestion FigureParams(const ImageWithParams& image_pack);