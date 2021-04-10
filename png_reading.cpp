#include <iostream>
#include <png.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "png_reading.h"

void abort_(const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

png_info_t::~png_info_t() {
    for (y=0; y<height; y++)
        free(row_pointers[y]);
    free(row_pointers);
}

void read_png_file(const char* file_name, png_info_t& pngInfo)
{
    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp)
        abort_("[read_png_file] File %s could not be opened for reading", file_name);
    fread(header, 1, 8, fp);


    /* initialize stuff */
    pngInfo.png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!pngInfo.png_ptr)
        abort_("[read_png_file] png_create_read_struct failed");

    pngInfo.info_ptr = png_create_info_struct(pngInfo.png_ptr);
    if (!pngInfo.info_ptr)
        abort_("[read_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(pngInfo.png_ptr)))
        abort_("[read_png_file] Error during init_io");

    png_init_io(pngInfo.png_ptr, fp);
    png_set_sig_bytes(pngInfo.png_ptr, 8);

    png_read_info(pngInfo.png_ptr, pngInfo.info_ptr);

    pngInfo.width = png_get_image_width(pngInfo.png_ptr, pngInfo.info_ptr);
    pngInfo.height = png_get_image_height(pngInfo.png_ptr, pngInfo.info_ptr);
    pngInfo.color_type = png_get_color_type(pngInfo.png_ptr, pngInfo.info_ptr);
    pngInfo.bit_depth = png_get_bit_depth(pngInfo.png_ptr, pngInfo.info_ptr);

    pngInfo.number_of_passes = png_set_interlace_handling(pngInfo.png_ptr);
    png_read_update_info(pngInfo.png_ptr, pngInfo.info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(pngInfo.png_ptr)))
        abort_("[read_png_file] Error during read_image");

    pngInfo.row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pngInfo.height);
    for (int y=0; y<pngInfo.height; y++)
        pngInfo.row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(pngInfo.png_ptr,pngInfo.info_ptr));

    png_read_image(pngInfo.png_ptr, pngInfo.row_pointers);

    fclose(fp);
}