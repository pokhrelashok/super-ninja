#include "Level.h"
#include <fstream>
#include <sstream>
#include <iostream>

Level::Level(Shader &shader, Texture &texture) : shader(shader), texture(texture) {};
void Level::load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
  // clear old data
  this->tiles.clear();
  // load from file
  char tileCode;
  std::string line;
  std::ifstream fstream(file);
  std::vector<std::vector<char>> tileData;
  if (fstream)
  {
    while (std::getline(fstream, line)) // read each line from level file
    {
      std::istringstream sstream(line);
      std::vector<char> row;
      while (sstream >> tileCode)
      {
        row.push_back(tileCode);
      } // read each word separated by spaces
      tileData.push_back(row);
    }
    if (tileData.size() > 0)
      this->init(tileData, levelWidth, levelHeight);
  }
}

void Level::draw()
{
  for (Sprite &tile : this->tiles)
    tile.render();
}

void Level::init(std::vector<std::vector<char>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
  // calculate dimensions
  unsigned int height = tileData.size();
  unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
  float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / height;
  // initialize level tiles based on tileData
  for (unsigned int y = 0; y < height; ++y)
  {
    for (unsigned int x = 0; x < width; ++x)
    {
      if (tileData[y][x] == '-')
      {
        glm::vec2 pos(unit_width * x, unit_height * y);
        glm::vec2 size(unit_width, unit_height);
        glm::vec2 sprPos(15, 1);
        if (x == width - 1)
          sprPos.y = 2;
        else if (x == 0)
          sprPos.y = 0;
        else if (tileData[y][x - 1] == 'g' && tileData[y][x + 1] == 'g')
          sprPos = glm::vec2(12, 4);
        else if (tileData[y][x - 1] == 'g')
          sprPos = glm::vec2(15, 0);
        else if (tileData[y][x + 1] == 'g')
          sprPos = glm::vec2(15, 2);

        Sprite obj(shader, texture, pos, size, glm::vec2(32.0f, 32.0f), sprPos);
        this->tiles.push_back(obj);
      }
    }
  }
}