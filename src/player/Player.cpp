#include "Player.h"
#include "../physics/Physics.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

int currentFrame = 0;
float frameTime = 0;

std::pair currentAnim = std::make_pair(0, 0);
Physics physics = Physics();
const float DURATION_IN_FRAME = 0.20f;

Player::Player(Shader &s, Texture &t, glm::vec2 position, glm::vec2 size, glm::vec2 spriteSize) : Sprite(s, t, position, size, spriteSize), state(PLAYER_STATE_IDLE) {
                                                                                                  };
void Player::update(bool keys[], std::vector<Sprite> &obstacles)
{

  glm::vec2 newPosition = position;

  if (keys[GLFW_KEY_SPACE] == true && isGrounded)
  {
    state = PLAYER_STATE_JUMPING;
    currentFrame = 0;
    frameTime = 0;
    velocity.y = -jumpVelocity;
  }
  else if (keys[GLFW_KEY_RIGHT] == true)
  {
    if (state != PLAYER_STATE_WALKING)
    {
      direction = 1.0f;
      if (state != PLAYER_STATE_JUMPING && state != PLAYER_STATE_RUN)
      {
        state = keys[GLFW_KEY_LEFT_SHIFT] ? PLAYER_STATE_RUN : PLAYER_STATE_WALKING;
        currentFrame = 0;
        frameTime = 0;
      }
    }
    newPosition.x += velocity.x * (state == PLAYER_STATE_RUN ? 2 : 1) * Time::delta;
  }
  else if (keys[GLFW_KEY_LEFT] == true)
  {
    if (state != PLAYER_STATE_WALKING)
    {
      direction = -1.0f;
      if (state != PLAYER_STATE_JUMPING && state != PLAYER_STATE_RUN)
      {
        state = keys[GLFW_KEY_LEFT_SHIFT] ? PLAYER_STATE_RUN : PLAYER_STATE_WALKING;
        currentFrame = 0;
        frameTime = 0;
      }
    }
    newPosition.x -= velocity.x * (state == PLAYER_STATE_RUN ? 2 : 1) * Time::delta;
  }
  else if (keys[GLFW_KEY_F] == true)
  {
    state = PLAYER_STATE_ATTACK;
    currentFrame = 0;
    frameTime = 0;
  }
  else
  {
    if ((state != PLAYER_STATE_JUMPING && state != PLAYER_STATE_ATTACK))
      this->reset_to_idle();
  }

  if (((state == PLAYER_STATE_JUMPING || state == PLAYER_STATE_ATTACK) && (currentFrame + 1 >= currentAnim.second)))
    this->reset_to_idle();

  // process animation
  currentAnim = get_current_animation();
  frameTime += Time::delta;
  if (frameTime >= DURATION_IN_FRAME)
  {
    currentFrame = (currentFrame + 1) % currentAnim.second;
    frameTime = 0;
  }
  float positionY = position.y;

  if (isAffectedByGravity && !isGrounded)
  {
    velocity.y += (GRAVITY * Time::delta) * 10;
    positionY = position.y + (velocity.y * Time::delta);
    newPosition.y = positionY;
  }
  spritePosition = glm::vec2(currentAnim.first, currentFrame);

  Collision collision;
  physics.detectCollision(newPosition, size, obstacles, collision);

  if (collision.hasCollided)
  {
    if (collision.bottom)
    {
      velocity.y = 0;
      newPosition.y = position.y;
      isGrounded = true;
    }
    if (collision.right || collision.left)
    {
      newPosition.x = position.x;
    }
  }
  else
  {
    isGrounded = false;
  }
  position = newPosition;
};

void Player::render()
{

  Sprite::render();
};

std::pair<int, int> Player::get_current_animation()
{
  if (state == PLAYER_STATE_IDLE)
  {
    // return std::make_pair(4, 6);
    return std::make_pair(0, 1);
  }
  if (state == PLAYER_STATE_JUMPING)
  {
    // return std::make_pair(3, 12);
    return std::make_pair(0, 12);
  }
  if (state == PLAYER_STATE_WALKING)
  {
    // return std::make_pair(0, 8);
    return std::make_pair(0, 1);
  }
  if (state == PLAYER_STATE_DEAD)
  {
    // return std::make_pair(6, 3);
    return std::make_pair(0, 1);
  }
  if (state == PLAYER_STATE_ATTACK)
  {
    // return std::make_pair(7, 3);
    return std::make_pair(0, 1);
  }
  if (state == PLAYER_STATE_RUN)
  {
    // return std::make_pair(2, 7);
    return std::make_pair(0, 1);
  }
}

void Player::reset_to_idle()
{
  state = PLAYER_STATE_IDLE;
  currentFrame = 0;
  frameTime = 0;
}
