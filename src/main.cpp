#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../OGLT/header/OGLT.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../OGLT/stb/stb_image_write.h"

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

int main() {
  oglt::OpenGL &opengl = oglt::OpenGL::CreateInstance();
  oglt::OpenGL::CreateWindow("Loupe");

  const oglt::CameraType& type = oglt::CameraType::OrthoCamera;

  oglt::OpenGL::CreateCamera(type);
  oglt::OpenGL::CreateMouse();

  oglt::OpenGL::CreateKeyHandler(type);
  oglt::OpenGL::CreateMouseHandler(type);

  oglt::OpenGL::CreateRenderer();
  {
    float width  = oglt::OpenGL::GetWindow()->GetWidth() * 1.0f;
    float height = oglt::OpenGL::GetWindow()->GetHeight() * 1.0f;

    float vertices[] = {
      // Position,          // Text Coord
      width,   0.0f,  0.0f, 1.0f, 1.0f,  // top right
      width, height,  0.0f, 1.0f, 0.0f,  // bottom right
      0.0f,  height,  0.0f, 0.0f, 0.0f,  // bottom left
      0.0f,    0.0f,  0.0f, 0.0f, 1.0f,  // top left 
    };

    uint32_t indices[] = {
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
    };

    opengl.CreateVAO();
    opengl.CreateVBO();
    opengl.CreateEBO();

    opengl.GetVAO().Bind();

    opengl.GetEBO().FlushData(indices, sizeof(indices));
    opengl.GetVBO().FlushData(vertices, sizeof(vertices));
  
    opengl.GetVAO().LinkVBO(opengl.GetVBO(), 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    opengl.GetVAO().LinkVBO(opengl.GetVBO(), 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    opengl.GetVAO().Unbind();
  }

  opengl.CreateTexture(oglt::TextureType::TextureType2D);
  opengl.GetTexture().LoadTexture("screenshot.png", GL_RGBA);
  while (!glfwWindowShouldClose(opengl.GetWindow()->GetOpenGLWindow())) {
    opengl.CalculateDeltaTime();
    
    oglt::OpenGL::GetKeyHandler().Handle(oglt::OpenGL::GetDeltaTime());
    oglt::OpenGL::GetMouseHandler().Handle(oglt::OpenGL::GetDeltaTime());

    oglt::OpenGL::GetRenderer().ClearScreen(0x282828FF);
    oglt::OpenGL::GetRenderer().ClearBitmask();

    oglt::OpenGL::GetCamera()->SetAspectRatio((float)oglt::OpenGL::GetWindow()->GetWidth() / (float)oglt::OpenGL::GetWindow()->GetHeight());
    oglt::OpenGL::GetCamera()->CalculatePositition();
    oglt::OpenGL::GetCamera()->SubmitPosition();

    opengl.GetVAO().Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    oglt::OpenGL::GetRenderer().SwapBuffers();
    oglt::OpenGL::PollEvents();
  }

  return 0;
}
