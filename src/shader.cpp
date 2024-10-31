#include "../include/shader.hpp"

Shader::Shader(std::string vs_path, std::string fs_path)
{
  std::ifstream file_stream;
  std::stringstream string_stream;
  unsigned int vertex_shader, fragment_shader;
  std::string source;
  const char* c_source;
  int success;
  char error_log[1024];

  file_stream.open(vs_path.c_str());
  if(!file_stream.is_open())
  {
    std::cout << "ERROR: VERTEX SHADER FILE NOT FOUND" << std::endl;
    return;
  }
  string_stream << file_stream.rdbuf();
  file_stream.close();

  source = string_stream.str();
  c_source = source.c_str();

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &c_source, NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex_shader, 1024, NULL, error_log);
    std::cout << "ERROR: VERTEX SHADER NOT WORKING\nReason: " << error_log << std::endl;
    return;
  }

  string_stream.clear();
  string_stream.str(std::string());

  file_stream.open(fs_path.c_str());
  if(!file_stream.is_open())
  {
    std::cout << "ERROR: FRAGMENT SHADER FILE NOT FOUND" << std::endl;
    return;
  }
  string_stream << file_stream.rdbuf();
  file_stream.close();

  source = string_stream.str();
  c_source = source.c_str();

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &c_source, NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment_shader, 1024, NULL, error_log);
    std::cout << "ERROR: FRAGMENT SHADER NOT WORKING\nReason: " << error_log << std::endl;
    return;
  }

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glCompileShader(shader_program);
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shader_program, 1024, NULL, error_log);
    std::cout << "ERROR: SHADER PROGRAM NOT WORKING\nReason: " << error_log << std::endl;
    return;
  }
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
  glDeleteProgram(shader_program);
}

unsigned int Shader::get_program() const
{
  return shader_program;
}
