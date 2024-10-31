#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
  Camera();
  glm::mat4 get_projection();
  glm::mat4 get_view();
private:
  glm::mat4 projection, view;
};
#endif
