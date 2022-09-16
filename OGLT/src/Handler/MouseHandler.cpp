#include "../../header/Handler/MouseHandler.hpp"

namespace oglt {
  MouseHandler::MouseHandler() {
  }

  MouseHandler::~MouseHandler() {
  }

  MouseHandler::MouseHandler(std::shared_ptr<Window>& window, std::shared_ptr<Mouse>& mouse, std::shared_ptr<Camera>& camera) {
    MouseHandler::SetWindow(window);
    MouseHandler::SetCamera(camera);
    MouseHandler::SetMouse(mouse);
  }

  MouseHandler::MouseHandler(std::shared_ptr<Window>& window, std::shared_ptr<Mouse>& mouse, std::shared_ptr<Camera>& camera, const CameraType& type) {
    MouseHandler::SetWindow(window);
    MouseHandler::SetCamera(camera);
    MouseHandler::SetMouse(mouse);
    MouseHandler::GetCamera()->SetCameraType(type);
  }

  void MouseHandler::Handle(float deltatime) {
    (void) deltatime;
    switch (MouseHandler::GetCamera()->GetCameraType()) {
    case CameraType::PerspecCamera:
      this->HandlePerspecCamera(deltatime);
      break;
    case CameraType::OrthoCamera:
      this->HandleOrthoCamera(deltatime);
      break;
    case CameraType::Undefined:
      std::cerr << "[OpenGL][Error]: Camera type should never be undefined ?" << std::endl;
      exit(1);
      break;
    default:
      break;
    }
  }

  void MouseHandler::HandlePerspecCamera(float deltatime) {
    MouseHandler::SetDeltatime(deltatime);
    MouseHandler::GetMouse()->SetMouseCursorCallback(MouseHandler::PerspecMouseCursorCallback, MouseHandler::GetWindow());
    MouseHandler::GetMouse()->SetMouseScrollCallback(MouseHandler::PerspecMouseScrollCallback, MouseHandler::GetWindow());
    MouseHandler::GetMouse()->SetMouseButtonCallback(MouseHandler::PerspecMouseButtonCallback, MouseHandler::GetWindow());
  }

  void MouseHandler::HandleOrthoCamera(float deltatime) {
    std::shared_ptr<Mouse>  mouse  = MouseHandler::GetMouse();
    std::shared_ptr<Window> window = MouseHandler::GetWindow();
    std::shared_ptr<Camera> camera = MouseHandler::GetCamera();

    MouseHandler::SetDeltatime(deltatime);
    mouse->SetMouseCursorCallback(MouseHandler::OrthoMouseCursorCallback, window);
    mouse->SetMouseScrollCallback(MouseHandler::OrthoMouseScrollCallback, window);
    mouse->SetMouseButtonCallback(MouseHandler::OrthoMouseButtonCallback, window);

    glm::vec3 translate = glm::vec3(0.0f);
    if (mouse->IsHeld()) {
      double xpos, ypos;
      glfwGetCursorPos(window->GetOpenGLWindow(), &xpos, &ypos);
      mouse->SetCurrentPosition(glm::vec2(xpos, ypos));
      translate += MouseHandler::ScreenToWorld(glm::vec3(mouse->GetCurrentPosition(), 0.0f) - glm::vec3(mouse->GetPreviousPosition(), 0.0f));
      mouse->SetPreviousPosition(glm::vec2(xpos, ypos));

      camera->SetTransformationMatrix(glm::translate(camera->GetTransformationMatrix(), -1.0f * translate));
    } else {
      mouse->SetPreviousPosition(glm::vec3(0.0f));
      mouse->SetCurrentPosition(glm::vec3(0.0f));
    }
  }

  void MouseHandler::PerspecMouseCursorCallback(GLFWwindow *window, double xPosIn, double yPosIn) {
    (void) window;
    (void) xPosIn;
    (void) yPosIn;

    double xpos = xPosIn;
    double ypos = yPosIn;

    int width;
    int height;

    if (MouseHandler::GetMouse()->IsFirstMouse()) {
      MouseHandler::GetMouse()->SetPreviousPosition(glm::vec2(xpos, ypos));
      MouseHandler::GetMouse()->SetFirstMouse(false);
    }

    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);

    float threashold = 10.0f;

    if (xpos < 0 + threashold) MouseHandler::GetCamera()->MoveLeft(MouseHandler::GetDeltatime());
    if (xpos > width - threashold) MouseHandler::GetCamera()->MoveRight(MouseHandler::GetDeltatime());
    if (ypos < 0 + threashold) MouseHandler::GetCamera()->MoveUp(MouseHandler::GetDeltatime());
    if (ypos > height - threashold) MouseHandler::GetCamera()->MoveDown(MouseHandler::GetDeltatime());
  }
 
  void MouseHandler::PerspecMouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    (void) window;
    (void) xoffset;
    (void) yoffset;

    // TODO:
    // 1. Get the world-space coordinates of the mouse cursor using the current zoom factor and model/proj/view matrices.
    // 2. Adjust zoom factor
    // 3. Get the world-space mouse coordinates again using the new zoom factor
    // 4. Shift the camera position by the difference in world-space mouse coordinates
    // 5. Redraw scene using new camera position and zoom factor

    MouseHandler::GetCamera()->SetFOV(MouseHandler::GetCamera()->GetFOV() - (2.0f * parametric_blend(yoffset) - 1) * 5.0f);
    if (MouseHandler::GetCamera()->GetFOV() < 1.0f) MouseHandler::GetCamera()->SetFOV(1.0f);
    if (MouseHandler::GetCamera()->GetFOV() > 180.0f) MouseHandler::GetCamera()->SetFOV(180.0f);
  }

  void MouseHandler::PerspecMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    (void) mods;
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
       double xpos, ypos;
       //getting cursor position (screen)
       glfwGetCursorPos(window, &xpos, &ypos);

       std::cout << "Cursor Position(screen) at (" << xpos << " : " << ypos << ")" << std::endl;
    }
  }

  void MouseHandler::OrthoMouseCursorCallback(GLFWwindow *window, double xPosIn, double yPosIn) {
    (void) window;
    (void) xPosIn;
    (void) yPosIn;
  }

  void MouseHandler::OrthoMouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    (void) window;
    (void) xoffset;

    glm::vec3 scale = glm::vec3(2.0f, 2.0f, 0.0f);

    std::shared_ptr<Camera> camera = MouseHandler::GetCamera();

    if (yoffset < 0) camera->SetTransformationMatrix(glm::scale(camera->GetTransformationMatrix(), scale));
    else if (yoffset > 0) camera->SetTransformationMatrix(glm::scale(camera->GetTransformationMatrix(), -1.0f * scale));
  }

  void MouseHandler::OrthoMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    (void) window;
    (void) button;
    (void) action;
    (void) mods;

    std::shared_ptr<Mouse> mouse = MouseHandler::GetMouse();

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      if (action == GLFW_PRESS) {
	mouse->SetHeldState(true);
	double x, y;
	glfwGetCursorPos(window, &x, &y);
      }
      else if (action == GLFW_RELEASE) mouse->SetHeldState(false);
    }
  }

  const glm::vec3 MouseHandler::WorldToScreen(const glm::vec3& position) {
    return position * MouseHandler::GetCamera()->GetScale();
  }

  const glm::vec3 MouseHandler::ScreenToWorld(const glm::vec3& position) {
    return position / MouseHandler::GetCamera()->GetScale();
  }
}
