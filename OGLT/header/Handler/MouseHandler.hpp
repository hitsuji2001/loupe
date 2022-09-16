#ifndef __MOUSE_HANDLER_HPP__
#define __MOUSE_HANDLER_HPP__

#include "./Handler.hpp"
#include "../Mouse.hpp"

namespace oglt {
  class MouseHandler final : public Handler {
  public:
    MouseHandler();
    MouseHandler(std::shared_ptr<Window>& window, std::shared_ptr<Mouse>& mouse, std::shared_ptr<Camera>& camera, const CameraType& type);
    MouseHandler(std::shared_ptr<Window>& window, std::shared_ptr<Mouse>& mouse, std::shared_ptr<Camera>& camera);
    virtual ~MouseHandler();

    void Handle(float deltatime) override;

  private:
    void HandlePerspecCamera(float deltatime);
    void HandleOrthoCamera(float deltatime);

    static const glm::vec3 WorldToScreen(const glm::vec3& position);
    static const glm::vec3 ScreenToWorld(const glm::vec3& position);

    static void PerspecMouseCursorCallback(GLFWwindow *window, double xPosIn, double yPosIn);
    static void PerspecMouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    static void PerspecMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

    static void OrthoMouseCursorCallback(GLFWwindow *window, double xPosIn, double yPosIn);
    static void OrthoMouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    static void OrthoMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
  };
}

#endif // __MOUSE_HANDLER_HPP__
