#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/shape.hpp"
#include "../include/game.hpp"

int main()
{
  Game game_world("OpenGL Sandbox Simulation", 1280, 720, 30.0f, "res/shaders/vertex.glsl", "res/shaders/normal_fragment.glsl", "res/shaders/light_fragment.glsl");

  glm::vec3 vertices[] = {
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f)
  };

  glm::vec3 colors[] = {
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 1.0f),
    glm::vec3(0.5f, 0.0f, 1.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 1.0f),
    glm::vec3(0.5f, 0.0f, 1.0f)
  };

  unsigned int indices[] = {
    0, 1, 2,
    0, 3, 2,
    0, 1, 5,
    0, 4, 5,
    0, 4, 7,
    0, 3, 7,
    6, 2, 1,
    6, 5, 1,
    6, 5, 4,
    6, 7, 4,
    6, 2, 3,
    6, 7, 3
  };


  Shape square(vertices, colors, indices, sizeof(vertices), sizeof(colors), sizeof(indices));
  game_world.add_entity(square);

  while(!game_world.should_close()) { game_world.game_loop(); }

  game_world.terminate();

  return 0;
}
