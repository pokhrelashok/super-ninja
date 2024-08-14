#pragma once
#include "../player/Player.h"
#include "../sprite/Sprite.h"
#include <iostream>
#include <vector>
struct Collision
{
  bool top;
  bool right;
  bool left;
  bool bottom;
  bool hasCollided;
};
const float GRAVITY = 9.8f;
class Physics
{
public:
  void detectCollision(glm::vec2 &position, glm::vec2 &size, std::vector<Sprite> &tiles, Collision &sides);
};
