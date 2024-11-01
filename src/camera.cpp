#include "../include/camera.hpp"
#include <GLFW/glfw3.h>

Camera::Camera(unsigned int width, unsigned int height):
  projection(glm::mat4(1.0f)), view(glm::mat4(1.0f)),
  pos(glm::vec3(0.0f, 0.0f, 3.0f)), dir(glm::vec3(0.0f, 0.0f, -1.0f)),
  up(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0f), pitch(0.0f)
{
  projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.01f, 100.0f);
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
  glm::vec3 move(0.0f), look;

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    move += speed * glm::normalize(glm::cross(dir, up));
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    move -= speed * glm::normalize(glm::cross(dir, up));
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    move.y += speed;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    move.y -= speed;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    move += speed * dir;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    move -= speed * dir;
  if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    yaw -= 0.809f;
  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    yaw += 0.809f;
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    pitch += 0.809f;
  if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    pitch -= 0.809f;

  if (pitch > 89.9f)
    pitch = 89.9f;
  if (pitch < -89.9f)
    pitch = -89.9f;

  look.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  look.y = sin(glm::radians(pitch));
  look.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  pos += move;
  dir = glm::normalize(look);

  view = glm::lookAt(pos, pos + dir, up);
}

void Camera::set_pos(glm::vec3 value, bool except_x, bool except_y, bool except_z)
{
  if (!except_x)
    pos.x = value.x;
  if (!except_y)
    pos.y = value.y;
  if (!except_z)
    pos.z = value.z;
  view = glm::lookAt(pos, pos + dir, up);
}
