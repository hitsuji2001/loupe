#include "../header/window.hpp"

OpenGLWindow::OpenGLWindow() {
  this->InitGLFW();
  this->SetUpAttributes();
}

OpenGLWindow::~OpenGLWindow() {

}

bool OpenGLWindow::CreateWindow(const char *title, uint32_t width, uint32_t height, bool fullscreen, bool centeredOnStartUp) {
  if (fullscreen) {
    this->a_WindowWidth = this->m_VideoMode->width;
    this->a_WindowHeight = this->a_WindowWidth;
  } else if (width != 0 and height != 0) {
    this->a_WindowWidth  = width;
    this->a_WindowHeight = height;
  } else if (width != 0 and height == 0) {
    this->a_WindowWidth  = width;
    this->a_WindowHeight = this->a_WindowWidth / 16 * 9;
  }
  this->a_WindowTitle = title;

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  if (!fullscreen) {
    this->m_Window = glfwCreateWindow(this->a_WindowWidth, this->a_WindowHeight, this->a_WindowTitle, NULL, NULL);
    if (this->m_Window == NULL) {
      std::cerr << "[Error]: Could not create Window\n";
      glfwTerminate();
      return false;
    }
    glfwDefaultWindowHints();

    if (!centeredOnStartUp) {
      glfwMakeContextCurrent(this->m_Window);
      glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);
      glfwShowWindow(this->m_Window);
    } else {
      int monitorX;
      int monitorY;
      glfwGetMonitorPos(this->m_Monitors[0], &monitorX, &monitorY);
      glfwSetWindowPos(this->m_Window,
		       monitorX + (this->m_VideoMode->width - this->a_WindowWidth) / 2.0f,
		       monitorY + (this->m_VideoMode->height - this->a_WindowHeight) / 2.0f);
      glfwShowWindow(this->m_Window);
    }
  } else {
    

 this->m_Window = glfwCreateWindow(this->a_WindowWidth, this->a_WindowHeight, this->a_WindowTitle, glfwGetPrimaryMonitor(), NULL);
    if (this->m_Window == NULL) {
      std::cerr << "[Error]: Could not create Window\n";
      glfwTerminate();
      return false;
    }
    glfwDefaultWindowHints();
  }
  glfwMakeContextCurrent(this->m_Window);
  glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);
  this->InitGLAD();
  return true;
}

void OpenGLWindow::SetMouseInputMode() {
  glfwSetInputMode(this->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow *OpenGLWindow::GetOpenGLWindow() {
  return this->m_Window;
}

uint32_t OpenGLWindow::GetWidth() {
  return this->a_WindowWidth;
}

uint32_t OpenGLWindow::GetHeight() {
  return this->a_WindowHeight;
}

void OpenGLWindow::SetWidth(uint32_t value) {
  this->a_WindowWidth = value;
}

void OpenGLWindow::SetHeight(uint32_t value) {
  this->a_WindowHeight = value;
}

bool OpenGLWindow::InitGLFW() {
  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return true;
}

bool OpenGLWindow::InitGLAD() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Could not initialize GLAD\n";
    return false;
  }
  return true;
}

void OpenGLWindow::SetUpAttributes() {
  this->m_Window = NULL;
  this->m_Monitors = glfwGetMonitors(&this->a_MonitorCount);
  this->m_VideoMode = glfwGetVideoMode(this->m_Monitors[0]);
  this->a_WindowWidth = this->m_VideoMode->width / 1.75f;
  this->a_WindowHeight = this->a_WindowWidth / 16 * 9;
}

void OpenGLWindow::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  (void) window;
  glViewport(0, 0, width, height);
}
