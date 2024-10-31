#ifndef SHAPE_HEADER
#define SHAPE_HEADER
#include <cstddef>
#include <glad/glad.h>
#include "shader.hpp"

class Shape
{
public:
  Shape(float* vertices, unsigned int* indices, size_t vertices_size, size_t indices_size);
  ~Shape();
  void draw(Shader shader) const;
private:
  unsigned int VBO, VAO, EBO, indices_count;
};
#endif
