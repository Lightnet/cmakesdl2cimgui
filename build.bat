@echo off
::make dir build
mkdir build
cd build
::cmake .. -DIMGUI_IMPL_OPENGL_LOADER_GLAD2=1
cmake ..
cmake --build .
pause
