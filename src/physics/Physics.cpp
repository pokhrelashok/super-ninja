#include "Physics.h";
int collisionCount = 0;
void Physics::detectCollision(glm::vec2 &position, glm::vec2 &size, std::vector<Sprite> &tiles, Collision &sides)
{
  for (Sprite tile : tiles)
  {
    sides.top = position.y < tile.position.y + tile.size.y;
    sides.right = position.x + size.x > tile.position.x;
    sides.bottom = position.y + size.y > tile.position.y;
    sides.left = position.x < tile.position.x + tile.size.x;

    if (sides.bottom)
    {
      collisionCount++;
      sides.hasCollided = true;
      return;
    };
  }
  sides.hasCollided = false;
}