#include "../header/Renderer.hpp"

namespace oglt {
  Renderer::Renderer() {
  }

  Renderer::~Renderer() {
  }

  Renderer::Renderer(const std::shared_ptr<Window>& window) {
    this->SetWindow(window);
  }

  void Renderer::ClearScreen(uint32_t hex_color) {
    float r, g, b, a;

    r = (float)((hex_color >> (8 * 3)) & 0xFF) / (float)0xFF;
    g = (float)((hex_color >> (8 * 2)) & 0xFF) / (float)0xFF;
    b = (float)((hex_color >> (8 * 1)) & 0xFF) / (float)0xFF;
    a = (float)((hex_color >> (8 * 0)) & 0xFF) / (float)0xFF;

    glClearColor(r, g, b, a);
  }

  void Renderer::ClearScreen(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
  }

  void Renderer::ClearBitmask(GLbitfield mask) {
    glClear(mask);
  }

  void Renderer::SwapBuffers() {
    glfwSwapBuffers(this->GetWindow()->GetOpenGLWindow());
  }

  void Renderer::SetWindow(const std::shared_ptr<Window>& window) {
    this->m_Window = window;
  }

  const std::shared_ptr<Window>& Renderer::GetWindow() {
    return this->m_Window;
  }
}
