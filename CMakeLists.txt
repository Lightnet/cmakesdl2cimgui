cmake_minimum_required(VERSION 3.20)
#[[
  work in progress
]]
message("[[===  Before Make Project ===]]")
#set(CMAKE_GENERATOR_PLATFORM x64) # -A x64
#set(CMAKE_GENERATOR_PLATFORM win32) # -A win32 # cmakelists doesn't work here

message("[[===  init Project ===]]")
# Project Name 
project(SDL2App)

# project info config to prefix name
#message("PROJECT_NAME:${PROJECT_NAME}")
#message("PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}")
#message("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")

# must set output build dir by default is none
message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# user must config manual
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}") # workspace/build/Debug
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

#================================================
# ENTRY POINT FILE / TEST
#================================================
#set(ENTRYPOINT WindowSDL2.cpp)
set(ENTRYPOINT tests/WindowSDL2ttf.cpp)
#================================================
# SETUP BUILD
#================================================
# https://github.com/haxpor/sdl2-cimgui-demo/blob/master/src/main.c
# https://github.com/canoi12/cimgui_c_sdl2_example/
# https://github.com/canoi12/cimgui_c_sdl2_example/blob/master/CMakeLists.txt
# https://stackoverflow.com/questions/15201064/cmake-conditional-preprocessor-define-on-code
#add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GL3W=0)
#add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD2=1)
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GL3W=0)
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW=0)
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD=0) #nope
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD2=1) #nope

#add_definitions(IMGUI_IMPL_OPENGL_LOADER_GL3W=0)
#add_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW=0)
#add_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD=0)
#add_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD2)

#TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GL3W=0 -DIMGUI_IMPL_OPENGL_LOADER_GLAD2=1)

#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD=1)
#target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_API=extern\ \"C\")
#target_compile_definitions(${PROJECT_NAME} IMGUI_IMPL_API=extern\ \"C\")
#target_compile_definitions(imgui_impl PRIVATE IMGUI_IMPL_API=extern\ \"C\") # fail

# 
set(ENABLE_FREETYPE ON)
set(ENABLE_SDL2 ON)
set(ENABLE_SDL2_TTF OFF)
set(ENABLE_SDL2_IMAGE OFF) # disable
set(ENABLE_SDL2_MIXER OFF) # disable
set(ENABLE_CIMGUI ON)

set(ENABLE_GLEW OFF) 
set(ENABLE_GL3W ON) 
set(ENABLE_GLAD OFF)
set(ENABLE_GLAD2 OFF)

set(SDL2_GIT_VERSION release-2.0.14) # SDL GIT RELEASE TAG
set(SDL_TTF_GIT_VERSION release-2.0.15) # SDL GIT RELEASE TAG
#set(SDL_IMAGE_GIT_VERSION release-2.0.5) # SDL GIT RELEASE TAG
set(SDL_IMAGE_GIT_VERSION  main) # SDL GIT RELEASE TAG
#set(SDL_MIXER_GIT_VERSION release-2.0.4) # SDL GIT RELEASE TAG
set(SDL_MIXER_GIT_VERSION master) # SDL GIT RELEASE TAG
#set(SDL_NET_GIT_VERSION master) # no cmakelists # 2021-04-14
#set(SDL_RTF_GIT_VERSION master) # no cmakelists # 2021-04-14

set(SDL2_ADDED true) # ALIAS DLL like SDL2::SDL2.lob

#message("OUTPUTCONFIG" OUTPUTCONFIG)
#message(  ${CMAKE_CONFIGURATION_TYPES} )
#message("OUTPUTCONFIG >>>>>>>>>>>" )

# build tools
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED true)
#set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  # 64 bits
  message("~ 64 BITS ~")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  # 32 bits
  message("~ 32 BITS ~")
endif()

# to deal with error log that rechecks paths
option(BUILD_CHECK_SDL "BUILD Check SDL path" ON)

set(CPP_INCLUDE_DIRS "")
set(CPP_SOURCE_FILES "")
set(CPP_HEADER_FILES "")

#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR};${CMAKE_MODULE_PATH}/cmake/sdl2")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
if(ENABLE_FREETYPE)
  if (NOT freetype_FOUND) # If there's none, fetch and build
    include(FetchContent)
    FetchContent_Declare(
      freetype
      GIT_REPOSITORY https://github.com/freetype/freetype.git
      GIT_TAG VER-2-10-4
      #GIT_TAG ${SDL_TTF_GIT_VERSION}
    )
    FetchContent_GetProperties(freetype)
    if (NOT freetype_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(freetype)
      message("freetype_LIBRARY: " ${freetype_LIBRARY}) # fail but define in cmake
      message("freetype_INCLUDE_DIR: " ${freetype_INCLUDE_DIR}) #pass
      message("freetype_SOURCE_DIR: " ${freetype_SOURCE_DIR}) # pass
      message("freetype_BINARY_DIR: " ${freetype_BINARY_DIR}) # pass

      #set(FT_WITH_ZLIB OFF CACHE BOOL "" FORCE)
      #set(FT_WITH_BZIP2 OFF CACHE BOOL "" FORCE)
      #set(FT_WITH_PNG OFF CACHE BOOL "" FORCE)
      #set(FT_WITH_HARFBUZZ OFF CACHE BOOL "" FORCE)
      #set(FT_WITH_BROTLI OFF CACHE BOOL "" FORCE)

      # build freetype
      list(APPEND CPP_INCLUDE_DIRS ${freetype_SOURCE_DIR}/include)
      list(APPEND CPP_INCLUDE_DIRS ${freetype_BINARY_DIR}/include)
      #list(APPEND CPP_INCLUDE_DIRS ${sdl_SOURCE_DIR}/src) #need for look for SDL.h
      #list(APPEND CPP_SOURCE_FILES ${sdl_SOURCE_DIR}/src)
      list(APPEND CPP_HEADER_FILES ${freetype_SOURCE_DIR}/include/ft2build.h)
      add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR}) #add to build in sub dir
      #link_directories(${sdl_ttf_BINARY_DIR}/Debug)# this will look for libs files.
      list(APPEND FREETYPE_INCLUDE_DIRS ${freetype_SOURCE_DIR}/include)
      list(APPEND FREETYPE_INCLUDE_DIRS ${freetype_BINARY_DIR}/include)

      #set(FREETYPE_INCLUDE_DIRS "${freetype_SOURCE_DIR}/include ${freetype_BINARY_DIR}/include")
      set(FREETYPE_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

      add_library(Freetype::Freetype ALIAS freetype)

    endif()
  endif()
endif()

message("~~~ SDL 2.0 BUILD! ~~~")
message("[[[=== CHECKING SDL DIR === ]]]")

#find_package(sdl2 REQUIRED)

if(ENABLE_SDL2)
  if (NOT sdl2_FOUND) # If there's none, fetch and build sdl
    include(FetchContent)
    FetchContent_Declare(
      sdl2
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG ${SDL2_GIT_VERSION}
    )
    FetchContent_GetProperties(sdl2)
    if (NOT sdl2_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(sdl2)
      message("SDL2_LIBRARY: " ${sdl2_LIBRARY}) # fail but define in cmake
      message("SDL2_INCLUDE_DIR: " ${sdl2_INCLUDE_DIR}) #pass
      message("SDL2_SOURCE_DIR: " ${sdl2_SOURCE_DIR}) # pass
      message("SDL2_BINARY_DIR: " ${sdl2_BINARY_DIR}) # pass
      # utility to setup the downloaded library for use
      #FetchContent_MakeAvailable(sdl2)
      # build SDL2
      list(APPEND CPP_INCLUDE_DIRS ${sdl2_BINARY_DIR}/include)
      list(APPEND CPP_INCLUDE_DIRS ${sdl2_SOURCE_DIR}/include)
      list(APPEND CPP_INCLUDE_DIRS ${sdl2_SOURCE_DIR}/src) 
      list(APPEND CPP_SOURCE_FILES ${sdl2_SOURCE_DIR}/include/SDL.h) #need for look for SDL.h

      #include_directories(${sdl2_SOURCE_DIR}/include) # do not include this that will mixed up the SDL_config.h
      include_directories(${sdl2_BINARY_DIR}/include)

      add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR}) #add to build in sub dir
      #link_directories(${sdl2_BINARY_DIR}/Debug)# this will look for libs files.
      #link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug)
      #add_library(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug)
      #add_library(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
      #set(SDL2_LIB_SDL2 NAMES sdl2d HINTS ${PROJECT_SOURCE_DIR}/build/Debug)

      list(APPEND SDL2_LIBRARIES ${PROJECT_SOURCE_DIR}/build/Debug/SDL2maind.lib)
      list(APPEND SDL2_LIBRARIES ${PROJECT_SOURCE_DIR}/build/Debug/SDL2-staticd.lib)
      list(APPEND SDL2_LIBRARIES ${PROJECT_SOURCE_DIR}/build/Debug/SDL2d.lib)

      list(APPEND SDL2_LIB ${PROJECT_SOURCE_DIR}/build/Debug/SDL2maind.lib)
      list(APPEND SDL2_LIB ${PROJECT_SOURCE_DIR}/build/Debug/SDL2-staticd.lib)
      list(APPEND SDL2_LIB ${PROJECT_SOURCE_DIR}/build/Debug/SDL2d.lib)

      #message("SDL2_ADDED ===============  " ${SDL2_ADDED})
      if (SDL2_ADDED)
        add_library(SDL2::SDL2 ALIAS SDL2)
        add_library(SDL2::SDL2-static ALIAS SDL2-static)
        #add_library(SDL2::SDL2-static ALIAS ${PROJECT_BINARY_DIR}/Debug/SDL2-staticd.lib)
        #add_library(FREETYPE::FREETYPE ALIAS FREETYPE)
        #add_library(Freetype::Freetype ALIAS ${PROJECT_BINARY_DIR}/Debug/freetyped.lib)
        #add_library(SDL2::SDL2 ALIAS ${PROJECT_BINARY_DIR}/Debug/SDL2d.lib)
      endif()

      #SDL2_DIR
      set(SDL2_DIR ${sdl2_BINARY_DIR})
    endif()
  endif()

  list(APPEND SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)

  list(APPEND SDL2_LIBRARY ${PROJECT_BINARY_DIR}/Debug/SDL2maind.lib)
  list(APPEND SDL2_LIBRARY ${PROJECT_BINARY_DIR}/Debug/SDL2-staticd.lib)
  list(APPEND SDL2_LIBRARY ${PROJECT_BINARY_DIR}/Debug/SDL2d.lib)
  #message(" SDL2_LIBRARY  ////////////   " ${SDL2_LIBRARY})
  # https://cmake.org/cmake/help/latest/command/link_directories.html
  #add_library(<name> ALIAS <target>)
  #add_library(SDL2main ALIAS ${PROJECT_SOURCE_DIR}/build/Debug/SDL2maind.lib)
  #add_library(SDL2-static ALIAS ${PROJECT_SOURCE_DIR}/build/Debug/SDL2-staticd.lib)
  #add_library(SDL2 ALIAS ${PROJECT_SOURCE_DIR}/build/Debug/SDL2d.lib)

  #link_directories(${PROJECT_BINARY_DIR}/Debug/SDL2maind.lib)
  #link_directories(${PROJECT_BINARY_DIR}/Debug/SDL2-staticd.lib)
  #ink_directories(${PROJECT_BINARY_DIR}/Debug/SDL2d.lib)
  link_directories(${PROJECT_BINARY_DIR}/Debug)

  #needed for sub library from sdl2_tff?
  list(APPEND SDL2_LIBRARY ${PROJECT_BINARY_DIR}/Debug/SDL2maind.lib)
  list(APPEND SDL2_LIBRARY ${PROJECT_BINARY_DIR}/Debug/SDL2-staticd.lib)
  list(APPEND SDL2_LIBRARY ${PROJECT_BINARY_DIR}/Debug/SDL2d.lib)

  list(APPEND SDL2_LIBRARIES ${PROJECT_BINARY_DIR}/Debug/SDL2maind.lib)
  list(APPEND SDL2_LIBRARIES ${PROJECT_BINARY_DIR}/Debug/SDL2-staticd.lib)
  list(APPEND SDL2_LIBRARIES ${PROJECT_BINARY_DIR}/Debug/SDL2d.lib)

  set(SDL2_PATH ${PROJECT_SOURCE_DIR}/build/Debug)
endif()

if(ENABLE_SDL2_TTF)
  if (NOT sdl_ttf_FOUND) # If there's none, fetch and build sdl
    include(FetchContent)
    FetchContent_Declare(
      sdl_ttf
      GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
      GIT_TAG ${SDL_TTF_GIT_VERSION}
    )
    FetchContent_GetProperties(sdl_ttf)
    if (NOT sdl_ttf_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(sdl_ttf)
      # utility to setup the downloaded library for use
      #FetchContent_MakeAvailable(sdl_ttf)
      #message("SDL_LIBRARY: " ${sdl_LIBRARY}) # fail but define in cmake
      #message("SDL_INCLUDE_DIR: " ${sdl_INCLUDE_DIR}) #pass
      message("sdl_ttf_SOURCE_DIR: " ${sdl_ttf_SOURCE_DIR}) # pass
      message("sdl_ttf_BINARY_DIR: " ${sdl_ttf_BINARY_DIR}) # pass
      # build SDL2
      #list(APPEND CPP_INCLUDE_DIRS ${sdl_ttf_SOURCE_DIR}/include)
      #list(APPEND CPP_INCLUDE_DIRS ${sdl_ttf_BINARY_DIR}/include)
      list(APPEND CPP_INCLUDE_DIRS ${sdl_ttf_SOURCE_DIR})
      #list(APPEND CPP_INCLUDE_DIRS ${sdl_SOURCE_DIR}/src) #need for look for SDL.h
      #list(APPEND CPP_SOURCE_FILES ${sdl_SOURCE_DIR}/src)
      include_directories(${sdl_ttf_SOURCE_DIR})
      #target_include_directories(${sdl_ttf} ${sdl2_SOURCE_DIR}/include) #fail
      include_directories(${sdl2_SOURCE_DIR}/include) #fail
      find_library(SDL2_LIB NAMES sdl2d HINTS ${PROJECT_SOURCE_DIR}/build/Debug)
      #add_library(${SDL2_LIB})
      #list(APPEND CPP_SOURCE_FILES ${sdl_ttf_SOURCE_DIR}/SDL_ttf.c)
      add_subdirectory(${sdl_ttf_SOURCE_DIR} ${sdl_ttf_BINARY_DIR}) #add to build in sub dir
      #link_directories(${sdl_ttf_BINARY_DIR}/Debug)# this will look for libs files.

      #link_directories(${PROJECT_BINARY_DIR}/Debug/SDL2_ttf.lib)

      list(APPEND CPP_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/_deps/sdl_ttf-src)
    endif()
  endif()
endif()

if(ENABLE_SDL2_IMAGE)
  if (NOT sdl_image_FOUND) # If there's none, fetch and build sdl
    include(FetchContent)
    FetchContent_Declare(
      sdl_image
      GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
      GIT_TAG ${SDL_IMAGE_GIT_VERSION}
    )
    FetchContent_GetProperties(sdl_image)
    if (NOT sdl_image_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(sdl_image)
      # utility to setup the downloaded library for use
      #FetchContent_MakeAvailable(sdl_image)

      list(APPEND CPP_INCLUDE_DIRS ${sdl_image_SOURCE_DIR})
      
      #set(SUPPORT_JPG OFF CACHE BOOL "" FORCE)
      #set(SUPPORT_PNG OFF CACHE BOOL "" FORCE)
      #set(BUILD_SHOWIMAGE OFF CACHE BOOL "" FORCE)
      #set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

      add_subdirectory(${sdl_image_SOURCE_DIR} ${sdl_image_BINARY_DIR}) #add to build in sub dir
    endif()
  endif()
endif()

if(ENABLE_SDL2_MIXER)
  if (NOT sdl_mixer_FOUND) # If there's none, fetch and build sdl
    include(FetchContent)
    FetchContent_Declare(
      sdl_mixer
      GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
      GIT_TAG ${SDL_MIXER_GIT_VERSION}
    )
    FetchContent_GetProperties(sdl_mixer)
    if (NOT sdl_mixer_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(sdl_mixer)
      # utility to setup the downloaded library for use
      #FetchContent_MakeAvailable(sdl_mixer)
      list(APPEND CPP_INCLUDE_DIRS ${sdl_mixer_SOURCE_DIR}/include)

      add_subdirectory(${sdl_mixer_SOURCE_DIR} ${sdl_mixer_BINARY_DIR}) #add to build in sub dir
    endif()
  endif()
endif()

message("~~~ CHECKING OPENGL... ~~~")

if(ENABLE_GLEW)
  if (NOT glewgit_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      glewgit
      URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip
    )
    FetchContent_GetProperties(glewgit)
    if (NOT glewgit_POPULATED) # Have we downloaded glfw yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(glewgit)
      
      include_directories(${glewgit_SOURCE_DIR}/include)
      list(APPEND CPP_INCLUDE_DIRS ${glewgit_SOURCE_DIR}/include)

      #add_subdirectory(${glfw_SOURCE_DIR})
      message("glewgit_SOURCE_DIR " ${glewgit_SOURCE_DIR})
      #message("glewgit_BINARY_DIR " ${glewgit_BINARY_DIR})
      #add_subdirectory(${glewgit_SOURCE_DIR} ${glewgit_BINARY_DIR})

    endif()
  endif()
endif()

if(ENABLE_GL3W)
  if (NOT gl3w_FOUND) # If there's none, fetch and build sdl
    include(FetchContent)
    FetchContent_Declare(
      gl3w
      GIT_REPOSITORY https://github.com/skaslev/gl3w.git
      GIT_TAG master
    )
    FetchContent_GetProperties(gl3w)
    if (NOT gl3w_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(gl3w)
      # utility to setup the downloaded library for use
      #FetchContent_MakeAvailable(gl3w)
      message("GL3W GITHUB ====================================   ")
      message("GL3W GITHUB SRC >>> " ${gl3w_SOURCE_DIR})
      message("GL3W GITHUB BIN >>> " ${gl3w_BINARY_DIR})

      list(APPEND CPP_INCLUDE_DIRS ${gl3w_BINARY_DIR}/include)
      list(APPEND CPP_INCLUDE_DIRS ${gl3w_BINARY_DIR}/src)

      list(APPEND CPP_HEADER_FILES ${gl3w_BINARY_DIR}/include/GL/gl3w.h)
      list(APPEND CPP_HEADER_FILES ${gl3w_BINARY_DIR}/src/gl3w.c)
      

      add_subdirectory(${gl3w_SOURCE_DIR} ${gl3w_BINARY_DIR}) #add to build in sub dir
    endif()
  endif()
endif()

if(ENABLE_GLAD)
  set(glad_DIR ${PROJECT_SOURCE_DIR}/thirdparty/glad)
  list(APPEND CPP_HEADER_FILES ${glad_DIR}/include/glad/glad.h)
  list(APPEND CPP_INCLUDE_DIRS ${glad_DIR}/include)
  #include_directories(${CPP_INCLUDE_DIRS})
endif()

if(ENABLE_GLAD2)
  set(glad_DIR ${PROJECT_SOURCE_DIR}/thirdparty/glad2)
  list(APPEND CPP_HEADER_FILES ${glad_DIR}/include/glad/gl.h)
  list(APPEND CPP_INCLUDE_DIRS ${glad_DIR}/include)

  include_directories(${CPP_INCLUDE_DIRS})
endif()

message("~~~ CHECKING GRAPHIC INTERFACE... ~~~")

if(ENABLE_CIMGUI)
  if (NOT cimgui_FOUND) # If there's none, fetch and build sdl
    include(FetchContent)
    FetchContent_Declare(
      cimgui
      GIT_REPOSITORY https://github.com/cimgui/cimgui.git
      GIT_TAG 1.82
    )
    FetchContent_GetProperties(cimgui)
    if (NOT cimgui_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(cimgui)
      # utility to setup the downloaded library for use
      #FetchContent_MakeAvailable(cimgui)
      #list(APPEND CPP_INCLUDE_DIRS ${cimgui_SOURCE_DIR})
      list(APPEND CPP_INCLUDE_DIRS ${cimgui_SOURCE_DIR}/imgui)
      list(APPEND CPP_INCLUDE_DIRS ${cimgui_SOURCE_DIR}/imgui/backends)

      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/cimgui.cpp)
      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/imgui/imgui.cpp)
      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/imgui/imgui_demo.cpp)
      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/imgui/imgui_draw.cpp)
      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/imgui/imgui_tables.cpp)
      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/imgui/imgui_widgets.cpp)

      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_sdl.cpp)
      list(APPEND CPP_SOURCE_FILES ${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp)

      list(APPEND CPP_HEADER_FILES ${cimgui_SOURCE_DIR}/cimgui.h)
      list(APPEND CPP_HEADER_FILES ${cimgui_SOURCE_DIR}/imgui/imgui.h)
      list(APPEND CPP_HEADER_FILES ${cimgui_SOURCE_DIR}/imgui/imconfig.h)
      list(APPEND CPP_HEADER_FILES ${cimgui_SOURCE_DIR}/imgui/imgui_internal.h)

      list(APPEND CPP_HEADER_FILES ${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_sdl.h)
      list(APPEND CPP_HEADER_FILES ${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h)

      #target_compile_definitions(cimgui PRIVATE IMGUI_IMPL_API=extern\ \"C\")

      add_subdirectory(${cimgui_SOURCE_DIR} ${cimgui_BINARY_DIR}) #add to build in sub dir
    endif()
  endif()
endif()

#message("PROJECT_BINARY_DIR "${PROJECT_BINARY_DIR})
# https://github.com/cpm-cmake/CPM.cmake/issues/144

include_directories(${CPP_INCLUDE_DIRS})

#================================================
# EXECUTE APPLICATION PROGRAM
#================================================
add_executable(${PROJECT_NAME}
	#${ENTRYPOINT}
  #tests/config_in.h
  #tests/helloworld.c
  #tests/helloworld.c
  tests/sdl2gl3wcimgui.c
  #tests/WindowSDL2.cpp
  #tests/WindowSDL2ttf.cpp
  #tests/sdl2gl3cimgui.c
  #tests/sdl2gl3w.cpp
  #tests/sdl2Image.cpp #not working yet
  ${CPP_HEADER_FILES}
  ${CPP_SOURCE_FILES}
)
# https://stackoverflow.com/questions/28395833/using-sdl2-with-cmake
target_link_libraries(${PROJECT_NAME} 
  PRIVATE
	SDL2main
	SDL2-static
  SDL2
  #freetype
  #SDL2_ttf
  cimgui
  #glu32
  #opengl32
  #SDL2_image
  #jpeg
)

#COPY FONT
set(FONT ${PROJECT_SOURCE_DIR}/font)
set(FONT_BIN ${PROJECT_BINARY_DIR}/Debug/font)
add_custom_target(copy-files-font ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${FONT}
    ${FONT_BIN}
)

set(IMAGES ${PROJECT_SOURCE_DIR}/images)
set(IMAGES_BIN ${PROJECT_BINARY_DIR}/Debug/images)
add_custom_target(copy-files-iamges ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${IMAGES}
    ${IMAGES_BIN}
)

message("[[=== END OF CMAKELIST ! ===]]")
#message("OS BIT ${CMAKE_SIZEOF_VOID_P}") #ok
#if (CMAKE_HOST_WIN32)
  #set(WINDOWS 1)
  #message("BUILD WIN32")
#elseif(CMAKE_HOST_APPLE)
  #set(MACOS 1)
  #message("BUILD MACOS")
#elseif(CMAKE_HOST_UNIX)
  #set(LINUX 1)
  #message("BUILD LINUX")
#endif()
#message("CDIR: ${CMAKE_CURRENT_LIST_DIR}")

#[[

]]
#install(TARGETS SDL2Test
  #CONFIGURATIONS Debug
  #DESTINATION ${PROJECT_BINARY_DIR}/bin
#)
#install (FILES "${PROJECT_SOURCE_DIR}/platforms/win/DynamsoftBarcodeReaderx86.dll" DESTINATION bin)
#install(TARGETS SDL2Test DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin)
#install(TARGETS SDL2Test DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin)
#install (FILES "${PROJECT_BINARY_DIR}/BarcodeReaderConfig.h" DESTINATION include)
#install (DIRECTORY "${PROJECT_SOURCE_DIR}/include" DESTINATION include)

