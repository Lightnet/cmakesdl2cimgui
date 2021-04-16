 * https://github.com/haxpor/sdl2-cimgui-demo/blob/master/src/main.c
 * https://github.com/canoi12/cimgui_c_sdl2_example/
 * https://github.com/canoi12/cimgui_c_sdl2_example/blob/master/CMakeLists.txt
 * https://stackoverflow.com/questions/15201064/cmake-conditional-preprocessor-define-on-code
 https://retifrav.github.io/blog/2019/05/26/sdl-imgui/

 https://retifrav.github.io/blog/2019/08/04/glfw-dear-imgui/


# SDL2:
```c++
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
  //bool err = gladLoadGL() == 0; //does not have it
  bool err = gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress) == 0;
#endif
```
 * https://github.com/Dav1dde/glad/issues/81