#include "../include/shape.hpp"

Shape::Shape(float* vertices, unsigned int* indices, size_t vertices_size, size_t indices_size)
  :indices_count(indices_size / sizeof(unsigned int))
{
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
  glEnableVertexAttribArray(0);
}

Shape::~Shape()
{
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
}

void Shape::draw(Shader shader) const
{
  glUseProgram(shader.get_program());
  glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
}
