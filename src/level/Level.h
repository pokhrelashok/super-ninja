#pragma once
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../sprite/Sprite.h"
#include "../shader/Shader.h"
#include "../texture/Texture.h"

class Level
{
public:
  Shader shader;
  Texture texture;
  // level state
  std::vector<Sprite> tiles;
  // constructor
  Level(Shader &shader, Texture &texture);
  // loads level from file
  void load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
  // render level
  void draw();
  // check if the level is completed (all non-solid tiles are destroyed)
  bool isCompleted();

private:
  // initialize level from tile data
  void init(std::vector<std::vector<char>> tileData,
            unsigned int levelWidth, unsigned int levelHeight);
};