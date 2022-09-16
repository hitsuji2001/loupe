#ifndef __KEY_HANDLER_HPP__
#define __KEY_HANDLER_HPP__

#include "./Handler.hpp"

namespace oglt {
  class KeyHandler : public Handler {
  public:
    KeyHandler();
    KeyHandler(std::shared_ptr<Window>& window, std::shared_ptr<Camera>& camera, const CameraType& type);
    KeyHandler(std::shared_ptr<Window>& window, std::shared_ptr<Camera>& camera);
    virtual ~KeyHandler();

    void Handle(float deltatime) override;
  private:
    void HandlePerspecCamera(float deltatime);
    void HandleOrthoCamera(float deltatime);
  };
}

#endif // __KEY_HANDLER_HPP__
