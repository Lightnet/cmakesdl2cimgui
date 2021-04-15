https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
https://www.javaer101.com/en/article/19901079.html
https://www.dealii.org/9.1.1/users/cmakelists.html
https://bytefreaks.net/programming-2/manually-set-the-cmake-output-folder


https://github.com/aminosbh/sdl2-cmake-modules

https://www.reddit.com/r/sdl/comments/asdjvr/sdl2_cmake_modules/

https://edgarluque.com/blog/sdl2-cmake


```cmake
# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.11)

# Project's name
project(hello)

# Set the output folder where your program will be created
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

add_executable(hello ${PROJECT_SOURCE_DIR}/hello.cpp)
```


```cmake
set_target_properties( targets...
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
```