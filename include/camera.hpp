#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
class Camera
{
public:
  Camera();
  glm::mat4 get_projection();
  glm::mat4 get_view();
  void input(GLFWwindow* window);
  void set_pos(glm::vec3 value, bool except_x, bool except_y, bool except_z);
private:
  glm::mat4 projection, view;
  glm::vec3 pos, dir;
};
#endif
