#include "../header/Mouse.hpp"

namespace oglt {
  Mouse::Mouse() {
    this->a_Sensitivty = 5.0f;

    this->a_CurrPos    = glm::vec2(0.0f);
    this->a_PrevPos    = glm::vec2(0.0f);
    this->a_FirstMouse = true;
    this->a_IsHeld     = false;
  }

  Mouse::~Mouse() {

  }

  bool Mouse::IsFirstMouse() const {
    return this->a_FirstMouse;
  }

  bool Mouse::IsHeld() const {
    return this->a_IsHeld;
  }

  float Mouse::GetSensitivity() const {
    return this->a_Sensitivty;
  }

  const glm::vec2& Mouse::GetCurrentPosition() {
    return this->a_CurrPos;
  }

  const glm::vec2& Mouse::GetPreviousPosition() {
    return this->a_PrevPos;
  }

  void Mouse::SetFirstMouse(bool value) {
    this->a_FirstMouse = value;
  }

  void Mouse::SetHeldState(bool value) {
    this->a_IsHeld = value;
  }

  void Mouse::SetMouseInputMode(const std::shared_ptr<Window>& window, int mode, int value) {
    glfwSetInputMode(window->GetOpenGLWindow(), mode, value);
  }

  void Mouse::DisableCursor(const std::shared_ptr<Window>& window) {
    glfwSetInputMode(window->GetOpenGLWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }    

  void Mouse::SetMouseCursorCallback(void (*callback)(GLFWwindow *window, double xPosIn, double yPosIn), std::shared_ptr<Window> window) {
    glfwSetCursorPosCallback(window->GetOpenGLWindow(), callback);
  }

  void Mouse::SetMouseScrollCallback(void (*callback)(GLFWwindow *window, double xOffset, double yOffet), std::shared_ptr<Window> window) {
    glfwSetScrollCallback(window->GetOpenGLWindow(), callback);
  }

  void Mouse::SetMouseButtonCallback(void (*callback)(GLFWwindow* window, int button, int action, int mods), std::shared_ptr<Window> window) {
    glfwSetMouseButtonCallback(window->GetOpenGLWindow(), callback);
  }

  void Mouse::SetCurrentPosition(const glm::vec2& value) {
    this->a_CurrPos = value;
  }

  void Mouse::SetPreviousPosition(const glm::vec2& value) {
    this->a_PrevPos = value;
  }
}
