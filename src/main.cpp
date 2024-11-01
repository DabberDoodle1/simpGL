#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/shader.hpp"
#include "../include/shape.hpp"
#include "../include/camera.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
  if (!glfwInit())
  {
    std::cout << "ERROR: GLFW NOT INITIALIZED" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Sandbox Simulation", NULL, NULL);

  if (!window)
  {
    std::cout << "ERROR: WINDOW NOT CREATED" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "ERROR: GLAD NOT INITIALIZED" << std::endl;
    glfwTerminate();
    return -1;
  }

  glEnable(GL_DEPTH_TEST);
/*
  glm::vec3 vertices[] = {
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f)
  };*/

  glm::vec3 vertices[20];

  glm::vec3 colors[20]/* = {
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 1.0f),
    glm::vec3(0.5f, 0.0f, 1.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 1.0f),
    glm::vec3(0.5f, 0.0f, 1.0f)
  }*/;

  float theta = 360.0f / 20.0f;

  for (int i = 0; i < 20; i++)
  {
    float value = glm::radians(theta * (i));
    glm::vec3 vec_val(cos(value), sin(value), 0.5f);
    vertices[i] = vec_val;
    if (value >= M_PI && value <= 3 * M_PI_2)
      colors[i] = glm::vec3(0.0f, 0.0f, 1.0f);
    else
      colors[i] = glm::vec3(vec_val.x, vec_val.y, 0.0f);
  }

  /*
  unsigned int indices[] = {
    0, 1, 2,
    0, 3, 2,
    0, 1, 5,
    0, 4, 5,
    0, 4, 7,
    0, 3, 7,
    6, 2, 1,
    6, 5, 1,
    6, 5, 4,
    6, 7, 4,
    6, 2, 3,
    6, 7, 3
  };*/

  unsigned int indices[60];

  for (int i = 0; i < 20; i++)
  {
    int index = i * 3;
    indices[index] = 0;
    indices[index + 1] = i + 1;
    indices[index + 2] = i + 2;
  }



  Shape square(vertices, colors, indices, sizeof(vertices), sizeof(colors), sizeof(indices));
  Shader shader("/home/THE_ALPHA_AND_THE_OMEGA/C++/simpGL/res/shaders/vertex.glsl", "/home/THE_ALPHA_AND_THE_OMEGA/C++/simpGL/res/shaders/fragment.glsl");
  Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);


  while (!glfwWindowShouldClose(window))
  {
    glfwSetKeyCallback(window, key_callback);
    camera.input(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    square.draw(camera, shader, 30.0f);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  square.terminate();
  shader.terminate();
  glfwTerminate();

  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
