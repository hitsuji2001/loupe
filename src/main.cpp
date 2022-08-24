#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../opengl-templates/header/opengl-template.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../opengl-templates/stb/stb_image_write.h"

void take_screenshot_and_save_to_file(const char *file_path = "screenshot.png") {
  Display *display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);

  XWindowAttributes win_att;
  XGetWindowAttributes(display, root, &win_att);

  int channels = 4;
  int width  = win_att.width;
  int height = win_att.height;
  
  XImage *img = XGetImage(display, root, 0, 0, win_att.width, win_att.height, AllPlanes, ZPixmap);

  uint8_t *data = new uint8_t[width * height * channels];

  uint64_t rm = img->red_mask;
  uint64_t gm = img->green_mask;
  uint64_t bm = img->blue_mask;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      uint64_t pixel = XGetPixel(img, x, y);
      
      uint8_t b = (pixel & bm) >> (8 * 0);
      uint8_t g = (pixel & gm) >> (8 * 1);
      uint8_t r = (pixel & rm) >> (8 * 2);

      data[(x + width * y) * channels + 0] = r;
      data[(x + width * y) * channels + 1] = g;
      data[(x + width * y) * channels + 2] = b;
      data[(x + width * y) * channels + 3] = 255;
    }
  }

  std::cout << "[INFO]: Writing image...." << std::endl;
  stbi_write_png(file_path, width, height, channels, data, width * channels);
  std::cout << "[INFO]: Done" << std::endl;
}

void process_input(GLFWwindow *window, Camera *camera, float deltaTime) {
  (void) camera;
  (void) deltaTime;
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
  float vertices[] = {
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top left 
  };

  uint32_t indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  OpenGL &opengl = OpenGL::CreateInstance();
  opengl.GetWindow()->CreateWindow("Loupe", 0, 0, true);

  opengl.SetCursorCallback();
  opengl.SetScrollCallback();

  opengl.GetShader()->LoadShaders("./shader/vertex.glsl", "./shader/fragment.glsl");

  opengl.SetVAO(new VAO());
  opengl.GetVAO()->Bind();

  opengl.SetEBO(new EBO(indices, sizeof(indices)));
  opengl.SetVBO(new VBO(vertices, sizeof(vertices)));
  
  opengl.GetVAO()->LinkVBO(opengl.GetVBO(), 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  opengl.GetVAO()->LinkVBO(opengl.GetVBO(), 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

  opengl.GetVAO()->Unbind();

  opengl.GetTexture()->CreateTexture(GL_TEXTURE_2D);
  opengl.GetTexture()->LoadTexture("screenshot.png", GL_RGBA);
  while (!glfwWindowShouldClose(opengl.GetWindow()->GetOpenGLWindow())) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    opengl.deltaTime = deltaTime;
    lastFrame = currentFrame;

    process_input(opengl.GetWindow()->GetOpenGLWindow(), opengl.GetCamera(), deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view       = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model      = glm::mat4(1.0f);

    view = glm::lookAt(opengl.GetCamera()->GetPosition(), opengl.GetCamera()->GetPosition() + opengl.GetCamera()->GetFrontVector(), opengl.GetCamera()->GetUpVector());
    projection = glm::perspective(glm::radians(opengl.GetCamera()->a_FOV), (float)opengl.GetWindow()->GetWidth() / (float)opengl.GetWindow()->GetHeight(), 0.1f, 100.0f);

    opengl.GetShader()->SetMat4("projection", projection);
    opengl.GetShader()->SetMat4("view", view);
    opengl.GetShader()->SetMat4("model", model);

    // opengl.GetTexture()->ActiveTexture(GL_TEXTURE0);

    opengl.GetShader()->Use();
    opengl.GetVAO()->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(opengl.GetWindow()->GetOpenGLWindow());
    glfwPollEvents();
  }

  return 0;
}
