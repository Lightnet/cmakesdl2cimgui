# sdl2windowcmake

# Packages:
 * SDL 2.0.14 (github)
 * freetype 2.10.4 (github)
 * SDL tff 2.0.15 (github)
 * CMake 3.20.1 (download)
 * VS 2019 (current build tested) (download)
 * cimgui

# Information:
  This is window 10 64 bit build. To used cmake build without need of editor with compiler but compile tool.

# Build:

# Note: 
 * The CMakeList.txt will download the SDL 2.0 files from github for easy to access. As well auto build the dlls.

```cmake

if (NOT freetype_FOUND)
...
add_library(Freetype::Freetype ALIAS freetype)
...
endif()

add_library(SDL2::SDL2 ALIAS SDL2) # required to set for window
add_library(SDL2::SDL2-static ALIAS SDL2-static)

```




# Credits:
  * Help of font loading.
    * https://github.com/grimfang4/SDL_FontCache
  * Help of library loading with SDL2::SDL2.lib
    * https://github.com/cpm-cmake/CPM.cmake/issues/144













