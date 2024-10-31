#ifndef SHADERS_HEADER
#define SHADERS_HEADER
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Shader
{
public:
  Shader(std::string vs_path, std::string fs_path);
  ~Shader();
  unsigned int get_program() const;
private:
  unsigned int shader_program;
};
#endif
