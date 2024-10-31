#ifndef SHADERS_HEADER
#define SHADERS_HEADER
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Shader
{
public:
  Shader(std::string vs_path, std::string fs_path);
  void set_matrix4f_uniform(std::string name, glm::mat4 matrix);
  void terminate();
  unsigned int get_program() const;
private:
  unsigned int shader_program;
};
#endif
