#pragma once

#include "GLFW/glfw3.h"

class Time
{
public:
  static float current;
  static float delta;
  static void tick();
};
