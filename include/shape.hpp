#ifndef SHAPE_HEADER
#define SHAPE_HEADER
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "camera.hpp"

class Shape
{
public:
  Shape(glm::vec3* vertices, glm::vec3* colors, unsigned int* indices, size_t vertices_size, size_t colors_size, size_t indices_size);
  void terminate();
  void draw(Camera camera, Shader shader) const;
private:
  unsigned int VBO, VAO, EBO, indices_count;
  glm::mat4 model;
};
#endif
