#pragma once
#include <glad/glad.h>
#include <string>
#include <GLFW/glfw3.h>

class Texture
{
public:
  unsigned int ID;
  int width, height;
  Texture(const char *path);
  void bind();
};