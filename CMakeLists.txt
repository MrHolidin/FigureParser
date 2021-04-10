cmake_minimum_required(VERSION 3.17)
project(FigureParser)

set(CMAKE_CXX_STANDARD 20)
# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config not found")
endif ()

# check for libpng
pkg_check_modules (LIBPNG libpng16 REQUIRED)
if (NOT LIBPNG_FOUND)
    message(FATAL_ERROR "You don't seem to have libpng16 development libraries installed")
else ()
    include_directories (${LIBPNG_INCLUDE_DIRS})
    link_directories (${LIBPNG_LIBRARY_DIRS})
    link_libraries (${LIBPNG_LIBRARIES})
endif ()
add_executable (FigureParser main.cpp ${LIBPNG_LINK_FLAGS} png_reading.cpp png_reading.h png_converting.h png_converting.cpp WhiteBlackImageParser.h Figures.h Figures.cpp WhiteBlackImageParser.cpp)