#include "../include/camera.hpp"

Camera::Camera()
  :projection(glm::mat4(1.0f)), view(glm::mat4(1.0f)), pos(glm::vec3(0.0f, 0.0f, 3.0f)), dir(glm::vec3(0.0f, 0.0f, -1.0f))
{
  projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 100.0f);
  view = glm::lookAt(pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::get_projection()
{
  return projection;
}

glm::mat4 Camera::get_view()
{
  return view;
}

void Camera::input(GLFWwindow* window)
{
  const float speed = 0.05f;
  glm::vec3 move(0.0f);

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    move.x += speed;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    move.x -= speed;
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    move.y += speed;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    move.y -= speed;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    move.z += speed;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    move.z -= speed;

  pos += move;
  view = glm::lookAt(pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::set_pos(glm::vec3 value, bool except_x, bool except_y, bool except_z)
{
  if (!except_x)
    pos.x = value.x;
  if (!except_y)
    pos.y = value.y;
  if (!except_z)
    pos.z = value.z;
  view = glm::lookAt(pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
