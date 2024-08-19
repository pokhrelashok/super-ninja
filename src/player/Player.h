#pragma once
#include "../ball/Ball.h"
#include "../shader/Shader.h"
#include "../sprite/Sprite.h"
#include "../texture/Texture.h"
#include "../time/Time.h"
#include <glm/glm.hpp>
#include <utility>
#include <vector>

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
  std::vector<Ball> balls;
  float jumpVelocity = 36.0f * 3;
  Player(Shader &s, Texture &t, glm::vec2 position, glm::vec2 size,
         glm::vec2 spriteSize, std::vector<Ball> balls);
  void render();
  void update(bool keys[], std::vector<Sprite> &obstacles);
  std::pair<int, int> get_current_animation();
  void reset_to_idle();
  bool isGrounded = false;
  glm::vec2 velocity = glm::vec2(100.0f, 0.0f);
};
