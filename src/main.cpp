#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/shader.hpp"
#include "../include/shape.hpp"

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
    std::cout << "ERROR: WINDOW NOT INITIALIZED" << std::endl;
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


  float vh = 300.0f / SCREEN_HEIGHT, vw = 300.0f / SCREEN_WIDTH;

  float vertices[] = {
    -vw, vh, 0.0f,
    vw, vh, 0.0f,
    vw, -vh, 0.0f,
    -vw, -vh, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 2,
    0, 3, 2
  };

  Shape square(vertices, indices, sizeof(vertices), sizeof(indices));


  Shader shader("/home/THE_ALPHA_AND_THE_OMEGA/C++/simpGL/res/shaders/vertex.glsl", "/home/THE_ALPHA_AND_THE_OMEGA/C++/simpGL/res/shaders/fragment.glsl");


  while (!glfwWindowShouldClose(window))
  {
    glfwSetKeyCallback(window, key_callback);

    glClearColor(1.0f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    square.draw(shader);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }


  glfwTerminate();

  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
