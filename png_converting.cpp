#include "png_converting.h"
#include <png.h>

ImageWithParams GetWhiteBlackImage(const png_info_t& pngInfo) {
    size_t height = pngInfo.height;
    size_t width = pngInfo.width;
    size_t BORDER_SUM_COLORS = 256 * 3 / 2;
    std::vector<std::vector<bool> > image(height, std::vector<bool>(width));
    for (size_t y=0; y<height; y++) {
        png_byte* row = pngInfo.row_pointers[y];
        for (size_t x=0; x<width; x++) {
            png_byte* ptr = &(row[x*3]);
            image[y][x] = (ptr[0] + ptr[1] + ptr[2] < BORDER_SUM_COLORS);
        }
    }
    return std::make_tuple(image, height, width);
}