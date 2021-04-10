#pragma once
#include "png_reading.h"
#include <vector>
#include <tuple>

using WhiteBlackImage = std::vector<std::vector<bool> >;
using ImageWithParams = std::tuple<WhiteBlackImage, size_t, size_t>;
std::tuple<WhiteBlackImage, size_t, size_t> GetWhiteBlackImage(const png_info_t& pngInfo);