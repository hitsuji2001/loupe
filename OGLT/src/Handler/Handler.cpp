#include "../../header/Handler/Handler.hpp"

namespace oglt {
  float                   Handler::a_Deltatime  = 0.0f;

  std::shared_ptr<Camera> Handler::m_Camera	= nullptr;
  std::shared_ptr<Mouse>  Handler::m_Mouse	= nullptr;
  std::shared_ptr<Window> Handler::m_Window	= nullptr;

  Handler::~Handler() {
  }

  const std::shared_ptr<Window>& Handler::GetWindow() {
    return Handler::m_Window;
  }

  const std::shared_ptr<Camera>& Handler::GetCamera() {
    return Handler::m_Camera;
  }

  const std::shared_ptr<Mouse>& Handler::GetMouse() {
    return Handler::m_Mouse;
  }

  float& Handler::GetDeltatime() {
    return Handler::a_Deltatime;
  }

  void Handler::SetCamera(const std::shared_ptr<Camera>& camera) {
    Handler::m_Camera = camera;
  }

  void Handler::SetWindow(const std::shared_ptr<Window>& window) {
    Handler::m_Window = window;
  }

  void Handler::SetMouse(const std::shared_ptr<Mouse>& mouse) {
    Handler::m_Mouse = mouse;
  }

  void Handler::SetDeltatime(float value) {
    Handler::a_Deltatime = value;
}
}
