#include "config_in.h"
#include <stdlib.h>
#include <stdio.h>

//int GLID = 0;
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
  #include "foo.h"
#endif


int main() {
  // printf() displays the string inside quotation
  printf("Hello, World!\n");

  printf("IMGUI_IMPL_OPENGL_LOADER_ %d\n", BAR);
  system("pause"); //this pauses the program until you press any key 
  return 0;
}