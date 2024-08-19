#pragma once

#include "../texture/Texture.h";
#include <string>
class Ball
{
public:
  float bounciness;
  float weight;
  float friction;
  std::string name;
  Texture &texture;
  Ball(std::string name, float weight, float bounciness, float friction, Texture &t);
};
