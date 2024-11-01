#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "../include/shader.hpp"
#include "../include/shape.hpp"
#include "../include/camera.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define RADIUS 3.45f

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

  float vh = 300.0f / SCREEN_HEIGHT, vw = 300.0f / SCREEN_WIDTH;

  glm::vec3 vertices[] = {
    glm::vec3(-vw, vh, vw), // LTF
    glm::vec3(vw, vh, vw), // RTF
    glm::vec3(vw, -vh, vw), // RBF
    glm::vec3(-vw, -vh, vw), // LBF
    glm::vec3(-vw, vh, -vw), // LFB
    glm::vec3(vw, vh, -vw), // RTB
    glm::vec3(vw, -vh, -vw), // RBB
    glm::vec3(-vw, -vh, -vw) // LBB
  };

  glm::vec3 colors[] = {
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 1.0f),
    glm::vec3(0.5f, 0.0f, 1.0f),
    glm::vec3(0.5f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.5f, 0.0f, 1.0f),
    glm::vec3(0.0f, 1.0f, 1.0f)
  };

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
  };


  Shape square(vertices, colors, indices, sizeof(vertices), sizeof(colors), sizeof(indices));
  Shader shader("/home/THE_ALPHA_AND_THE_OMEGA/C++/simpGL/res/shaders/vertex.glsl", "/home/THE_ALPHA_AND_THE_OMEGA/C++/simpGL/res/shaders/fragment.glsl");
  Camera camera;


  while (!glfwWindowShouldClose(window))
  {
    glfwSetKeyCallback(window, key_callback);
    camera.input(window);

    float theta_time = glfwGetTime();

    if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS)
    {
      float camera_x = static_cast<float>(sin(theta_time) * RADIUS);
      float camera_z = static_cast<float>(cos(theta_time) * RADIUS);
      camera.set_pos(glm::vec3(camera_x, 0.0f, camera_z), false, true, false);
    }

    //glClearColor(1.0f, 0.3f, 0.8f, 1.0f);
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
