#pragma once
#include "../texture/Texture.h"
#include "../shader/Shader.h"
#include <glm/glm.hpp>
class Sprite
{
private:
  unsigned int VAO, VBO;

public:
  Sprite(Shader &s, Texture &t, glm::vec2 position, glm::vec2 size, glm::vec2 spriteSize, glm::vec2 spriteCoord = glm::vec2(0, 0));
  glm::vec2 position, size, spritePosition;
  float direction = 1.0f;
  bool isAffectedByGravity = true;
  Shader &shader;
  Texture &texture;
  glm::vec2 spriteSize;
  void render();
};