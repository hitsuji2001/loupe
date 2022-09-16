#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <memory>

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./Window.hpp"

namespace oglt {
  class Renderer {
  public:
    Renderer();
    Renderer(const std::shared_ptr<Window>& window);
    virtual ~Renderer();

    void ClearScreen(uint32_t hex_color);
    void ClearScreen(const glm::vec4& color);
    void SwapBuffers();
    void ClearBitmask(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const std::shared_ptr<Window>& GetWindow();
    void SetWindow(const std::shared_ptr<Window>& window);
  private:
    std::shared_ptr<Window> m_Window;
  };
};

#endif // __RENDERER_HPP__
