#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
  unsigned int ID;

  Shader(const char *vertexPath, const char *fragmentPath);
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMatrix4(const std::string &name, glm::mat4 &matrix) const;
  void setVector2f(const std::string &name, glm::vec2 &value) const;
  void setVector3f(const std::string &name, glm::vec3 &value) const;

private:
  void checkCompileErrors(unsigned int shader, std::string type);
};