#ifndef GAME_WORLD
#define GAME_WORLD
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "camera.hpp"
#include "shape.hpp"
#include "shader.hpp"
class Game
{
  Shader* normal_shader;
  Shader* light_shader;
  Camera* camera;
  std::vector<Shape> entities;
  unsigned int window_width, window_height;
  float scale_factor;
  float last_frame;
  GLFWwindow* window;
public:
  Game(const char* title, unsigned int width, unsigned int height, float scale, const char* vertex_shader_path, const char* normal_frag_path, const char* light_frag_path);
  void terminate();
  void add_entity(Shape entity);
  void game_loop();
  int should_close();
private:
  void key_callback(float delta_time);
};
#endif
