#include <iostream>
#include "png_converting.h"
#include "WhiteBlackImageParser.h"
#include <vector>
#include <tuple>
#include <math.h>
#include <algorithm>
#include <string>




int main(int argc, char **argv)
{
    png_info_t pngInfo;
    std::string s;
    std::cin >> s;
    read_png_file(s.c_str(), pngInfo);
    auto answer = FigureParams(GetWhiteBlackImage(pngInfo));
    answer.Write(std::cout);
    return 0;
}
