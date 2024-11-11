#include "../include/game.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

Game::Game(const char* title, unsigned int width, unsigned int height, float scale, const char* vertex_shader_path, const char* normal_frag_path, const char* light_frag_path):
  scale_factor(scale),
  last_frame(0.0f),
  camera(new Camera(width, height))
{
  if (!glfwInit())
  {
    std::cout << "ERROR: GLFW NOT INITIALIZED" << std::endl;
    glfwTerminate();
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (!window)
  {
    std::cout << "ERROR: WINDOW NOT CREATED" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "ERROR: GLAD NOT INITIALIZED" << std::endl;
    glfwTerminate();
    return;
  }

  glEnable(GL_DEPTH_TEST);

  normal_shader = new Shader(vertex_shader_path, normal_frag_path);
  light_shader = new Shader(vertex_shader_path, light_frag_path);
}

void Game::terminate()
{
  for (Shape entity : entities)
    entity.terminate();

  normal_shader->terminate();
  delete normal_shader;

  light_shader->terminate();
  delete light_shader;

  delete camera;
  glfwTerminate();
}

void Game::add_entity(Shape entity) { entities.push_back(entity); }

void Game::game_loop()
{
  double current_time = glfwGetTime();
  double delta_time = current_time - last_frame;
  last_frame = current_time;
  key_callback((float)delta_time);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (Shape entity : entities)
    entity.draw(camera, normal_shader, scale_factor);

  glfwSwapBuffers(window);

  glfwPollEvents();
}

int Game::should_close()
{
  if (glfwWindowShouldClose(window))
    return 1;
  return 0;
}

void Game::key_callback(float delta_time)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);


  const float move_speed = 1.5f * delta_time;
  const float look_speed = 22.5f * delta_time;
  glm::vec3 move(0.0f), look, up(0.0f, 1.0f, 0.0f);

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    move += move_speed * glm::normalize(glm::cross(camera->dir, up));
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    move -= move_speed * glm::normalize(glm::cross(camera->dir, up));
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    move += move_speed * up;;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    move -= move_speed * up;
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    move += move_speed * camera->dir;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    move -= move_speed * camera->dir;
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camera->yaw -= look_speed;
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera->yaw += look_speed;
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    camera->pitch += look_speed;
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camera->pitch -= look_speed;

  if (camera->pitch > 89.9f)
    camera->pitch = 89.9f;
  if (camera->pitch < -89.9f)
    camera->pitch = -89.9f;

  float yaw_rad = glm::radians(camera->yaw), pitch_rad = glm::radians(camera->pitch);
  float sin_yaw = sin(yaw_rad), cos_yaw = cos(yaw_rad), sin_pitch = sin(pitch_rad), cos_pitch = cos(pitch_rad);

  look.x = cos_yaw * cos_pitch;
  look.y = sin_pitch;
  look.z = sin_yaw * cos_pitch;

  camera->pos += move;
  camera->dir = look;

  camera->view = glm::lookAt(camera->pos, camera->pos + camera->dir, up);
}
