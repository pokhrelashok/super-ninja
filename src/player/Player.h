#pragma once
#include "../sprite/Sprite.h"
#include "../texture/Texture.h"
#include "../shader/Shader.h"
#include "../time/Time.h"
#include <glm/glm.hpp>
#include <utility>

enum PLAYER_STATE
{
  PLAYER_STATE_IDLE,
  PLAYER_STATE_WALKING,
  PLAYER_STATE_JUMPING,
  PLAYER_STATE_DEAD,
  PLAYER_STATE_ATTACK,
  PLAYER_STATE_RUN,
};

class Player : public Sprite
{
public:
  PLAYER_STATE state;
  float jumpVelocity = -50.0f;
  Player(Shader &s, Texture &t, glm::vec2 position, glm::vec2 size, glm::vec2 spriteSize);
  void render();
  void update();
  std::pair<int, int> get_current_animation();
  void process_input(bool keys[]);
  void reset_to_idle();
  bool isGrounded = true;
  glm::vec2 velocity = glm::vec2(100.0f, 0.0f);
};