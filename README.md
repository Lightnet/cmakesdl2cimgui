# cmakesdl2cimgui

# Packages:
 * SDL 2.0.14 (github)
 * freetype 2.10.4 (github)
 * SDL tff 2.0.15 (github)
 * CMake 3.20.1 (download and install)
 * VS 2019 (current build tested) (download)
 * cimgui 1.82 https://github.com/cimgui/cimgui
 * Gl3w https://github.com/skaslev/gl3w
 * Python (need for gl3w to build files include and src)

# Information:
  This is window 10 64 bit build. To used cmake build without need of editor with compiler but compile tool.

# Build:
  Install CMake and chose of build tool compiler.

  Command Line:
```
mkdir build
cd build
cmake ..
cmake --build .
```
  Please note that currently set to window and it not config for other platform.

# Note: 
 * The CMakeList.txt will download the SDL 2.0 files from github and other add ons for easy to access. As well auto build the dlls, include, src and other setting on CMakeLists.txt.
 * If on window and with firewall or security that will block compile build commands.

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
  * Help with direction of SDL2 build.
    * https://github.com/cimgui/cimgui
  * Trouble shoot compile.
    * https://github.com/ocornut/imgui













