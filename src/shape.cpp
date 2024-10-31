#include "../include/shape.hpp"
#include <glm/ext/matrix_transform.hpp>

Shape::Shape(glm::vec3* vertices, glm::vec3* colors, unsigned int* indices, size_t vertices_size, size_t colors_size, size_t indices_size)
  :indices_count(indices_size / sizeof(unsigned int))
{
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, vertices_size + colors_size, 0, GL_DYNAMIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, vertices);
  glBufferSubData(GL_ARRAY_BUFFER, vertices_size, colors_size, colors);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(vertices_size));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-0.45f, 0.65f, -5.5f));
}

void Shape::terminate()
{
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
}

void Shape::draw(Camera camera, Shader shader) const
{
  glBindVertexArray(VAO);
  glUseProgram(shader.get_program());
  shader.set_matrix4f_uniform("model", model);
  shader.set_matrix4f_uniform("projection", camera.get_projection());
  glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
}
