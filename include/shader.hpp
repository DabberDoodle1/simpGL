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
  Shader(const char* vs_path, const char* fs_path);
  ~Shader();
  void set_matrix4(std::string name, glm::mat4 matrix) const;
  void set_vec3(std::string name, glm::vec3 value) const;
  void terminate();
  unsigned int get_program() const;
private:
  unsigned int shader_program;
};
#endif
