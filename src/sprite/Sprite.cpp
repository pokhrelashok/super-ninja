#include "Sprite.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <iomanip>
#include "../time/Time.h"

const float VERTICES[] = {
    // pos      // tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f};

Sprite::Sprite(Shader &s, Texture &t, glm::vec2 position, glm::vec2 size, glm::vec2 spriteSize, glm::vec2 tilePosition) : shader(s), texture(t), position(position), size(size), spriteSize(spriteSize), tilePosition(tilePosition)
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::render()
{
  shader.use();
  texture.bind();

  glm::mat4 projection = glm::ortho(0.0f, 640.0f, 640.0f, 0.0f, -1.0f, 1.0f);
  glm::mat4 model = glm::mat4(1.0f);

  // Translate to the model's center first
  model = glm::translate(model, glm::vec3(position + size / 2.0f, 0.0f));
  // model = glm::translate(model, glm::vec3(0.0f, positionY, 0.0f));
  // Flip the model
  if (direction == -1.0f)
  {
    model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  }
  // Translate back to the original position
  model = glm::translate(model, glm::vec3(-size / 2.0f, 0.0f));
  model = glm::scale(model, glm::vec3(size, 1.0f));

  shader.setMatrix4("model", model);
  shader.setMatrix4("projection", projection);

  float topLeftX = (spriteSize.x * tilePosition.y) / texture.width;
  float topLeftY = (spriteSize.y * tilePosition.x) / texture.height;
  float middleRightX = (spriteSize.x * (tilePosition.y + 1)) / texture.width;
  float middleRightY = (spriteSize.y * (tilePosition.x + 1)) / texture.height;

  const float vertices[] = {
      // pos      // tex
      0.0f, 1.0f, topLeftX, topLeftY,
      1.0f, 0.0f, middleRightX, middleRightY,
      0.0f, 0.0f, topLeftX, middleRightY,

      0.0f, 1.0f, topLeftX, topLeftY,
      1.0f, 1.0f, middleRightX, topLeftY,
      1.0f, 0.0f, middleRightX, middleRightY};

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}
