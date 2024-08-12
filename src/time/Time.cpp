#include "Time.h"
float Time::current = 0.0f;
float Time::delta = 0.0f;

void Time::tick()
{
  float t = glfwGetTime();
  delta = t - current;
  current = t;
}