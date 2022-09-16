#include "../../header/Handler/KeyHandler.hpp"

namespace oglt {
  KeyHandler::KeyHandler() {
  }

  KeyHandler::~KeyHandler() {
  }

  KeyHandler::KeyHandler(std::shared_ptr<Window>& window, std::shared_ptr<Camera>& camera, const CameraType& type) {
    KeyHandler::SetWindow(window);
    KeyHandler::SetCamera(camera);
    KeyHandler::GetCamera()->SetCameraType(type);
  }

  KeyHandler::KeyHandler(std::shared_ptr<Window>& window, std::shared_ptr<Camera>& camera) {
    KeyHandler::SetWindow(window);
    KeyHandler::SetCamera(camera);
  }

  void KeyHandler::HandlePerspecCamera(float deltatime) {
    (void) deltatime;
    GLFWwindow *window = KeyHandler::GetWindow()->GetOpenGLWindow();
    std::shared_ptr<Camera> camera = KeyHandler::GetCamera();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or
	glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      glfwSetWindowShouldClose(KeyHandler::GetWindow()->GetOpenGLWindow(), true);
  }

  void KeyHandler::HandleOrthoCamera(float deltatime) {
    (void) deltatime;
    GLFWwindow *window = KeyHandler::GetWindow()->GetOpenGLWindow();
    std::shared_ptr<Camera> camera = KeyHandler::GetCamera();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or
	glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      glfwSetWindowShouldClose(KeyHandler::GetWindow()->GetOpenGLWindow(), true);
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) KeyHandler::GetCamera()->SetTransformationMatrix(glm::mat4(1.0f));
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) KeyHandler::GetCamera()->MoveUp(deltatime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) KeyHandler::GetCamera()->MoveLeft(deltatime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) KeyHandler::GetCamera()->MoveDown(deltatime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) KeyHandler::GetCamera()->MoveRight(deltatime);
  }

  void KeyHandler::Handle(float deltaTime) {
    switch (KeyHandler::GetCamera()->GetCameraType()) {
    case CameraType::PerspecCamera:
      this->HandlePerspecCamera(deltaTime);
      break;
    case CameraType::OrthoCamera:
      this->HandleOrthoCamera(deltaTime);
      break;
    case CameraType::Undefined:
      std::cerr << "[OpenGL][Error]: Camera type should never be `undefined`?" << std::endl;
      exit(1);
      break;
    default:
      break;
    }
  }
}
