#include "shader/Shader.h"
#include "time/Time.h"
#include "texture/Texture.h"
#include "sprite/Sprite.h"
#include "level/Level.h"
#include "player/Player.h"
#include <glm/glm.hpp>
#include <iostream>

const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 640;
bool keys[1024];

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
      keys[key] = true;
    else if (action == GLFW_RELEASE)
    {
      keys[key] = false;
    }
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int main()
{

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Super Ninja", 0, 0);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  if (window == 0)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glfwSetKeyCallback(window, key_callback);
  Shader ourShader = Shader("res/shaders/common.vs", "res/shaders/common.fs");
  Texture backgroundTex = Texture("res/background.jpg");
  Texture playerTex = Texture("res/ball.png");
  Texture groundTex = Texture("res/ground.png");

  Level one = Level(ourShader, groundTex);
  one.load("res/one.lvl", SCR_WIDTH, SCR_HEIGHT);

  Sprite background = Sprite(ourShader, backgroundTex, glm::vec2(0, 0), glm::vec2(SCR_WIDTH, SCR_HEIGHT), glm::vec2(800, 800));
  background.isAffectedByGravity = false;
  Player player = Player(ourShader, playerTex, glm::vec2(0, SCR_HEIGHT - 400), glm::vec2(40, 40), glm::vec2(256, 256));

  while (!glfwWindowShouldClose(window))
  {
    Time::tick();
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    background.render();
    player.update(keys, one.tiles);
    one.draw();
    player.render();

    glfwSwapBuffers(window);
  }
  glfwTerminate();
};