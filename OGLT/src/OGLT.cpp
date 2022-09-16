#define STB_IMAGE_IMPLEMENTATION
#include "../header/OGLT.hpp"

namespace oglt {
  float    OpenGL::a_DeltaTime				= 0.0f;
  float    OpenGL::a_LastFrame				= 0.0f;

  std::shared_ptr<Window>   OpenGL::m_Window		= nullptr;
  std::shared_ptr<Camera>   OpenGL::m_ViewCamera	= nullptr;
  std::shared_ptr<Mouse>    OpenGL::m_Mouse		= nullptr;

  std::unique_ptr<Handler>  OpenGL::m_MouseHandler	= nullptr;
  std::unique_ptr<Handler>  OpenGL::m_KeyHandler	= nullptr;
  std::unique_ptr<Renderer> OpenGL::m_Renderer          = nullptr;

  OpenGL::OpenGL() {
    this->m_Shader		= nullptr;
    this->m_Texture		= nullptr;

    this->m_KeyHandler		= nullptr;
    this->m_MouseHandler	= nullptr;

    this->m_VAO			= nullptr;
    this->m_VBO			= nullptr;
    this->m_EBO			= nullptr;
  }

  OpenGL::~OpenGL() {
    glfwTerminate();
  }

  float OpenGL::GetDeltaTime() {
    return OpenGL::a_DeltaTime;
  }

  const std::shared_ptr<Shader>& OpenGL::GetShader() {
    return this->m_Shader;
  }

  std::shared_ptr<Camera>& OpenGL::GetCamera() {
    return OpenGL::m_ViewCamera;
  }

  std::shared_ptr<Mouse>& OpenGL::GetMouse() {
    return OpenGL::m_Mouse;
  }

  std::shared_ptr<Window>& OpenGL::GetWindow() {
    return OpenGL::m_Window;
  }

  Texture& OpenGL::GetTexture() {
    return *this->m_Texture;
  }

  Handler& OpenGL::GetKeyHandler() {
    return *OpenGL::m_KeyHandler;
  }

  Handler& OpenGL::GetMouseHandler() {
    return *OpenGL::m_MouseHandler;
  }

  Renderer& OpenGL::GetRenderer() {
    return *OpenGL::m_Renderer;
  }

  VAO& OpenGL::GetVAO() {
    return *this->m_VAO;
  }

  VBO& OpenGL::GetVBO() {
    return *this->m_VBO;
  }

  EBO& OpenGL::GetEBO() {
    return *this->m_EBO;
  }

  void OpenGL::CreateWindow(const std::string& title, const WindowType& type, int width, int height) {
    if (OpenGL::m_Window == nullptr) {
      OpenGL::m_Window = std::make_shared<Window>();
      OpenGL::GetWindow()->CreateWindow(title, type, width, height);
    }
  }

  void OpenGL::CreateShaders(const std::string& vertexPath, const std::string& fragmentPath) {
    // [TODO]: Maybe we could have multiple shaders,
    // so find a way to handle that.
    // Right now we just support 1 of each type of shader.
    if (this->m_Shader == nullptr) {
      this->m_Shader = std::make_shared<Shader>(vertexPath, fragmentPath);
    } else {
      this->m_Shader->LoadShaders(vertexPath, fragmentPath);
    }
  }

  void OpenGL::CreateCamera(const CameraType& type) {
    if (OpenGL::m_ViewCamera == nullptr) {
      switch (type) {
      case CameraType::OrthoCamera: {
	  int width  = OpenGL::GetWindow()->GetWidth();
	  int height = OpenGL::GetWindow()->GetHeight();

	  // float aspect = (float)width / (float) height;
	  // float scaler = 0.5f;
	  // OpenGL::m_ViewCamera = std::make_unique<OrthographicCamera>(-scaler * aspect, scaler * aspect, scaler * aspect, -scaler * aspect, 0.1f, 100.0f);
	  OpenGL::m_ViewCamera = std::make_unique<OrthographicCamera>(0, width, 0, height, 0.1f, 100.0f);
	  break;
	}
      case CameraType::PerspecCamera:
	OpenGL::m_ViewCamera = std::make_unique<PerspectiveCamera>();
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

  void OpenGL::CreateMouse() {
    if (OpenGL::m_Mouse == nullptr) OpenGL::m_Mouse = std::make_unique<Mouse>();
  }

  void OpenGL::CreateTexture(TextureType type, GLint wrapping, GLint filter) {
    // [TODO]: We certainly need multiple textures,
    // so find a way to deal with that.
    if (this->m_Texture == nullptr) {
      if (type == TextureType::TextureType2D) this->m_Texture = std::make_unique<Texture2D>();
      else if (type == TextureType::TextureType3D) this->m_Texture = std::make_unique<Texture3D>();
    } else {
      std::cerr << "[TODO]: Handle this case bro" << std::endl;
      exit(1);
    }

    this->m_Texture->CreateTexture(wrapping, filter);
  }

  void OpenGL::CreateKeyHandler(const CameraType& type) {
    if (OpenGL::m_KeyHandler == nullptr) {
      OpenGL::m_KeyHandler = std::make_unique<KeyHandler>(OpenGL::m_Window,
							  OpenGL::m_ViewCamera, type);
    }
  }

  void OpenGL::CreateMouseHandler(const CameraType& type) {
    if (OpenGL::m_MouseHandler == nullptr) {
      (void) type;
      OpenGL::m_MouseHandler = std::make_unique<MouseHandler>(OpenGL::m_Window,
							      OpenGL::m_Mouse,
							      OpenGL::m_ViewCamera);
    }
  }

  void OpenGL::CreateVAO() {
    // [TODO]: Multiple VAOs?
    if (this->m_VAO == nullptr) this->m_VAO = std::make_unique<VAO>();
  }

  void OpenGL::CreateVBO() {
    // [TODO]: Multiple VBOs?
    if (this->m_VBO == nullptr) this->m_VBO = std::make_unique<VBO>();
  }

  void OpenGL::CreateEBO() {
    // [TODO]: Multiple EBOs?
    if (this->m_EBO == nullptr) this->m_EBO = std::make_unique<EBO>();
  }

  void OpenGL::CreateRenderer() {
    if (OpenGL::m_Renderer == nullptr) OpenGL::m_Renderer = std::make_unique<Renderer>(OpenGL::GetWindow());
  }

  void OpenGL::PollEvents() {
    glfwPollEvents();
  }

  void OpenGL::WaitEvents() {
    glfwWaitEvents();
  }

  void OpenGL::CalculateDeltaTime() {
    float currentFrame = glfwGetTime();
    OpenGL::a_DeltaTime = currentFrame - OpenGL::a_LastFrame;
    OpenGL::a_LastFrame = currentFrame;
  }
}
