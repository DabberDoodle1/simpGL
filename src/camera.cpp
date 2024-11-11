#include "../include/camera.hpp"

Camera::Camera(unsigned int width, unsigned int height):
  projection(glm::mat4(1.0f)), view(glm::mat4(1.0f)),
  pos(glm::vec3(0.0f, 0.0f, 3.0f)), dir(glm::vec3(0.0f, 0.0f, -1.0f)),
  yaw(-90.0f), pitch(0.0f)
{
  projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.01f, 100.0f);
  view = glm::lookAt(pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::get_projection() { return projection; }

glm::mat4 Camera::get_view() { return view; }
