#pragma once
#include <png.h>

struct png_info_t { ;
    int x, y;
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
    ~png_info_t();
};

void abort_(const char * s, ...);

void read_png_file(const char* file_name, png_info_t& pngInfo);