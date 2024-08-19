#pragma once

#include <string>
class Ball {
public:
  float bounciness;
  float weight;
  float friction;
  std::string name;
  Ball(std::string name, float weight, float bounciness, float friction);
};
