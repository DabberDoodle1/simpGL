#include "../include/camera.hpp"

Camera::Camera()
  :projection(glm::mat4(1.0f)), view(glm::mat4(1.0f))
{
  projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 100.0f);
}

glm::mat4 Camera::get_projection()
{
  return projection;
}

glm::mat4 Camera::get_view()
{
  return view;
}
