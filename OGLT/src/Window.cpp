#include "../header/Window.hpp"

namespace oglt {
  Window::Window() {
    this->InitGLFW();
    this->SetUpAttributes();
  }

  Window::~Window() {
  }

  void Window::CreateWindow(const std::string& title, WindowType type, int width, int height) {
    switch (type) {
    case WindowType::BorderlessFullscreen:
      this->CreateBorderlessFullscreenWindow(title);
      break;
    case WindowType::Fullscreen:
      this->CreateFullScreenWindow(title);
      break;
    case WindowType::Normal:
      this->CreateNormalWindow(title, width, height);
      break;
    case WindowType::WindowedCentered:
      this->CreateCenteredWindow(title, width, height);
      break;
    default:
      break;
    }
  }

  bool Window::IsOpen() {
    return glfwWindowShouldClose(this->m_Window);
  }

  bool Window::CreateNormalWindow(const std::string& title, uint32_t width, uint32_t height) {
    if (width != 0 and height != 0) {
      this->a_Width  = width;
      this->a_Height = height;
    } else if (width != 0 and height == 0) {
      this->a_Width  = width;
      this->a_Height = this->a_Width / 16 * 9;
    }
    this->a_Title = title;

    this->m_Window = glfwCreateWindow(this->a_Width, this->a_Height, this->a_Title.c_str(), NULL, NULL);
    if (this->m_Window == NULL) {
      std::cerr << "[OpenGL][Error]: Could not create Window\n";
      glfwTerminate();
      return false;
    }
    glfwDefaultWindowHints();
    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);
    this->InitGLAD();
    return true;
  }

  bool Window::CreateFullScreenWindow(const std::string& title) {
    this->a_Width = this->m_VideoMode->width;
    this->a_Height = this->a_Width;
    this->a_Title = title;

    this->m_Window = glfwCreateWindow(this->a_Width, this->a_Height, this->a_Title.c_str(), glfwGetPrimaryMonitor(), NULL);
    if (this->m_Window == NULL) {
      std::cerr << "[OpenGL - Error]: Could not create Window\n";
      glfwTerminate();
      return false;
    }
    glfwDefaultWindowHints();
    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);

    this->InitGLAD();
    return true;
 }

  bool Window::CreateCenteredWindow(const std::string& title, uint32_t width, uint32_t height) {
    if (width != 0 and height != 0) {
      this->a_Width  = width;
      this->a_Height = height;
    } else if (width != 0 and height == 0) {
      this->a_Width  = width;
      this->a_Height = this->a_Width / 16 * 9;
    }
    this->a_Title = title;

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    this->m_Window = glfwCreateWindow(this->a_Width, this->a_Height, this->a_Title.c_str(), NULL, NULL);
    if (this->m_Window == NULL) {
      std::cerr << "[OpenGL][Error]: Could not create Window\n";
      glfwTerminate();
      return false;
    }
    int monitorX;
    int monitorY;
    glfwGetMonitorPos(this->m_Monitors[0], &monitorX, &monitorY);
    glfwSetWindowPos(this->m_Window,
		     monitorX + (this->m_VideoMode->width - this->a_Width) / 2.0f,
		     monitorY + (this->m_VideoMode->height - this->a_Height) / 2.0f);
    glfwShowWindow(this->m_Window);
 
    glfwDefaultWindowHints();
    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);

    this->InitGLAD();
    return true;
  }

  bool Window::CreateBorderlessFullscreenWindow(const std::string& title) {
    const GLFWvidmode *mode = glfwGetVideoMode(*this->m_Monitors);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    this->a_Width = mode->width;
    this->a_Height = mode->height;
    this->a_Title = title;

    this->m_Window = glfwCreateWindow(this->a_Width, this->a_Height, this->a_Title.c_str(), *this->m_Monitors, NULL);
    if (this->m_Window == NULL) {
      std::cerr << "[OpenGL][Error]: Could not create Window\n";
      glfwTerminate();
      return false;
    }

    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(this->m_Window, this->FramebufferSizeCallback);

    this->InitGLAD();
    return true;
  }

  GLFWwindow *Window::GetOpenGLWindow() {
    return this->m_Window;
  }

  uint32_t Window::GetWidth() {
    return this->a_Width;
  }

  uint32_t Window::GetHeight() {
    return this->a_Height;
  }

  void Window::SetWidth(uint32_t value) {
    this->a_Width = value;
  }

  void Window::SetHeight(uint32_t value) {
    this->a_Height = value;
  }

  bool Window::InitGLFW() {
    if (!glfwInit()) {
      std::cerr << "Could not initialize GLFW\n";
      return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
  }

  bool Window::InitGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      std::cerr << "Could not initialize GLAD\n";
      return false;
    }

    int gl_ver_major = glfwGetWindowAttrib(this->m_Window, GLFW_CONTEXT_VERSION_MAJOR);
    int gl_ver_minor = glfwGetWindowAttrib(this->m_Window, GLFW_CONTEXT_VERSION_MINOR);
    fprintf(stdout, "[OpenGL][Info]: Loaded OpenGL version: %d.%d\n", gl_ver_major, gl_ver_minor);

    return true;
  }

  void Window::SetUpAttributes() {
    this->m_Window = NULL;
    this->m_Monitors = glfwGetMonitors(&this->a_MonitorCount);
    this->m_VideoMode = glfwGetVideoMode(this->m_Monitors[0]);
    this->a_Width = this->m_VideoMode->width / 1.75f;
    this->a_Height = this->a_Width / 16 * 9;
  }

  void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    (void) window;
    glViewport(0, 0, width, height);
  }
}
