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
 * glad 0.1.34 https://github.com/Dav1dde/glad
 * glad 2.0
 * glew 2.20 https://github.com/nigels-com/glew

# Information:
  This was tested in window 10 64 bit build. This for imgui that is coded in c lanuage test build with cmake. It is branch off from https://github.com/ocornut/imgui to https://github.com/cimgui/cimgui that worked on to 1.82 version.

# Build:
  Install CMake and chose of build tool compiler. Note that opengl required other packages depend on the operating system.

  The next part is tricky. Is to chose which opengl package to used. GL3W, GLEW, GLAD and GLAD2.

```cmake
#CMakeLists.txt
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GL3W=0) # imgui_impl_opengl3.h # imgui Default to GL3W embedded in our repository
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW=0)
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD=0)
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD2=0)
```
  You need to comment them out but one must be uncomment to used opengl.
```cmake
#CMakeLists.txt
set(ENABLE_GL3W ON) # works #default from imgui
set(ENABLE_GLEW OFF) # work
set(ENABLE_GLAD OFF) # work
set(ENABLE_GLAD2 OFF) # work
```
  As well for this settings.

  Once that is done. But note that gl3w to build files with python 3.9.4.

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

# Dev Notes:
```
Download first time. Then set not to recheck when connect to internet or recompile. This will speed things up.

# https://bewagner.net/programming/2020/05/02/cmake-fetchcontent/
#set(FETCHCONTENT_FULLY_DISCONNECTED ON) # When this option is enabled, no attempt is made to download or update any content.
set(FETCHCONTENT_UPDATES_DISCONNECTED ON) # Skip Update
```

```c
//some code will error on main
#include <SDL.h>
#define main SDL_main
#undef main
```
## c in vulkan:
  Not much src or example files for c language setup. There are few but it take time to look at how it works. From vulkan, sdl and other yet look into yet. There one example file each but it a lot in one file.

# Credits:
  * Help of font loading.
    * https://github.com/grimfang4/SDL_FontCache
  * Help of library loading with SDL2::SDL2.lib
    * https://github.com/cpm-cmake/CPM.cmake/issues/144
  * Help with direction of SDL2 build.
    * https://github.com/cimgui/cimgui
  * Trouble shoot compile.
    * https://github.com/ocornut/imgui
