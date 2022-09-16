#ifndef __MOUSE_HPP__
#define __MOUSE_HPP__

#include <memory>

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./Window.hpp"

namespace oglt {
  class Window;

  class Mouse {
  public:
    void SetMouseInputMode(const std::shared_ptr<Window>& window, int mode, int value);
    void DisableCursor(const std::shared_ptr<Window>& window);

    void SetMouseCursorCallback(void (*callback)(GLFWwindow *window, double xPosIn, double yPosIn), std::shared_ptr<Window> window);
    void SetMouseScrollCallback(void (*callback)(GLFWwindow *window, double xOffset, double yOffset), std::shared_ptr<Window> window);
    void SetMouseButtonCallback(void (*callback)(GLFWwindow* window, int button, int action, int mods), std::shared_ptr<Window> window);
    void SetFirstMouse(bool value);
    void SetHeldState(bool value);

    void SetCurrentPosition(const glm::vec2& value);
    void SetPreviousPosition(const glm::vec2& value);

    bool  IsFirstMouse() const;
    bool  IsHeld() const;
    float GetSensitivity() const;

    const glm::vec2& GetCurrentPosition();
    const glm::vec2& GetPreviousPosition();

    Mouse();
    virtual ~Mouse();

  private:
    float     a_Sensitivty;
    bool      a_FirstMouse;
    bool      a_IsHeld;

    glm::vec2 a_CurrPos;
    glm::vec2 a_PrevPos;
  };
}

#endif // __MOUSE_HPP__
