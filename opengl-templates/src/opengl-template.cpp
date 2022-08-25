#include "../header/opengl-template.hpp"

Camera *OpenGL::m_Camera = new Camera();
Mouse  *OpenGL::m_Mouse  = new Mouse();
float OpenGL::deltaTime = 0.0f;

OpenGL::OpenGL() {
  this->m_Window  = new OpenGLWindow();
  this->m_Shader  = new Shader();

  this->m_Texture = new Texture();
  this->m_VAO     = NULL;
  this->m_VBO     = NULL;
  this->m_EBO     = NULL;
}

void OpenGL::SetCursorCallback() {
  glfwSetCursorPosCallback(this->m_Window->GetOpenGLWindow(), this->CursorCallback);
}

void OpenGL::SetScrollCallback() {
  glfwSetScrollCallback(this->m_Window->GetOpenGLWindow(), this->ScrollCallback);
}

void OpenGL::SetCamera(Camera *camera) {
  OpenGL::m_Camera = camera;
}

void OpenGL::SetMouse(Mouse *mouse) {
  OpenGL::m_Mouse = mouse;
}

void OpenGL::SetVAO(VAO *vao) {
  this->m_VAO = vao;
}

void OpenGL::SetVBO(VBO *vbo) {
  this->m_VBO = vbo;
}

void OpenGL::SetEBO(EBO *ebo) {
  this->m_EBO = ebo;
}

void OpenGL::CleanUp() {
  delete this->m_Texture;

  delete this->m_Shader;
  delete this->m_Window;

  if (this->m_EBO != NULL) {
    this->m_EBO->Delete();
    delete this->m_EBO;
  }
  if (this->m_VAO != NULL) {
    this->m_VAO->Delete();
    delete this->m_VAO;
  }
  if (this->m_VBO != NULL) {
    this->m_VBO->Delete();
    delete this->m_VBO;
  }

  delete OpenGL::m_Camera;
  delete OpenGL::m_Mouse;
}

OpenGL::~OpenGL() {
  this->CleanUp();
  glfwTerminate();
}

Shader *OpenGL::GetShader() {
  return this->m_Shader;
}

Camera *OpenGL::GetCamera() {
  return OpenGL::m_Camera;
}

Mouse *OpenGL::GetMouse() {
  return OpenGL::m_Mouse;
}

OpenGLWindow *OpenGL::GetWindow() {
  return this->m_Window;
}

Texture *OpenGL::GetTexture() {
  return this->m_Texture;
}

VAO *OpenGL::GetVAO() {
  return this->m_VAO;
}

VBO *OpenGL::GetVBO() {
  return this->m_VBO;
}

EBO *OpenGL::GetEBO() {
  return this->m_EBO;
}

void OpenGL::CursorCallback(GLFWwindow *window, double xPosIn, double yPosIn) {
  (void) window;
  (void) xPosIn;
  (void) yPosIn;

  double xpos = xPosIn;
  double ypos = yPosIn;

  int width;
  int height;

  if (OpenGL::m_Mouse->IsFirstMouse()) {
    OpenGL::m_Mouse->SetLastXPos(xpos);
    OpenGL::m_Mouse->SetLastYPos(ypos);
    OpenGL::m_Mouse->SetFirstMouse(false);
  }

  glfwGetCursorPos(window, &xpos, &ypos);
  glfwGetWindowSize(window, &width, &height);

  float threashold = 10.0f;

  if (xpos < 0 + threashold) OpenGL::GetCamera()->MoveLeft(OpenGL::deltaTime);
  if (xpos > width - threashold) OpenGL::GetCamera()->MoveRight(OpenGL::deltaTime);
  if (ypos < 0 + threashold) OpenGL::GetCamera()->MoveUp(OpenGL::deltaTime);
  if (ypos > height - threashold) OpenGL::GetCamera()->MoveDown(OpenGL::deltaTime);
}

void OpenGL::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
  (void) window;
  (void) xoffset;
  (void) yoffset;

  // TODO:
  // 1. Get the world-space coordinates of the mouse cursor using the current zoom factor and model/proj/view matrices.
  // 2. Adjust zoom factor
  // 3. Get the world-space mouse coordinates again using the new zoom factor
  // 4. Shift the camera position by the difference in world-space mouse coordinates
  // 5. Redraw scene using new camera position and zoom factor

  OpenGL::m_Camera->a_FOV -= (2.0f * parametric_blend(yoffset) - 1) * 5.0f;
  if (OpenGL::m_Camera->a_FOV < 1.0f) OpenGL::m_Camera->a_FOV = 1.0f;
}
