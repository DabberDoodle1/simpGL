#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
class Camera
{
public:
  Camera(unsigned int width, unsigned int height);
  glm::mat4 get_projection();
  glm::mat4 get_view();
  glm::mat4 projection, view;
  glm::vec3 pos, dir;
  float yaw, pitch;
};
#endif
