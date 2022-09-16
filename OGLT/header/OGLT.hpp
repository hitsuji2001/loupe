#ifndef __OPENGL_TEMPLATE_HPP__
#define __OPENGL_TEMPLATE_HPP__

#include "./Shader.hpp"
#include "./Window.hpp"
#include "./Mouse.hpp"

#include "./Camera/Camera.hpp"
#include "./Camera/PerspectiveCamera.hpp"
#include "./Camera/OrthographicCamera.hpp"

#include "./BufferObject/VAO.hpp"
#include "./BufferObject/VBO.hpp"
#include "./BufferObject/EBO.hpp"

#include "./Texture/Texture.hpp"
#include "./Texture/Texture2D.hpp"
#include "./Texture/Texture3D.hpp"

#include "./Handler/Handler.hpp"
#include "./Handler/KeyHandler.hpp"
#include "./Handler/MouseHandler.hpp"

#include "./Renderer.hpp"

namespace oglt {
  class OpenGL {
  public:
    static OpenGL &CreateInstance() {
      static OpenGL opengl;
      return opengl;
    }
    virtual ~OpenGL();

    const std::shared_ptr<Shader>& GetShader();
    Texture&  GetTexture();

    /// WILL CHANGE ///
    VAO&      GetVAO();
    VBO&      GetVBO();
    EBO&      GetEBO();
    /// WILL CHANGE ///

    static std::shared_ptr<Window>&   GetWindow();
    static std::shared_ptr<Camera>&   GetCamera();
    static std::shared_ptr<Mouse>&    GetMouse();

    static Handler&                   GetKeyHandler();
    static Handler&                   GetMouseHandler();
    static Renderer&                  GetRenderer();
    static float                      GetDeltaTime();

    static void PollEvents();
    static void WaitEvents();
    static void CalculateDeltaTime();

    void CreateShaders(const std::string& vertexPath, const std::string& fragmentPath);
    void CreateTexture(TextureType type, GLint wrapping = GL_REPEAT, GLint filter = GL_LINEAR);

    static void CreateWindow(const std::string& title, const WindowType& type = WindowType::WindowedCentered, int width = 0, int height = 0);
    static void CreateCamera(const CameraType& type);
    static void CreateMouse();
    static void CreateKeyHandler(const CameraType& type);
    static void CreateMouseHandler(const CameraType& type);
    static void CreateRenderer();

    /// WILL CHANGE ///
    void CreateVAO();
    void CreateVBO();
    void CreateEBO();
    /// WILL CHANGE ///

  protected:
    OpenGL();
    OpenGL(const OpenGL&) = delete;

  private:
    void CleanUp();

  private:
    static float                        a_DeltaTime;
    static float                        a_LastFrame;

    static std::shared_ptr<Window>	m_Window;
    static std::shared_ptr<Camera>      m_ViewCamera;
    static std::shared_ptr<Mouse>       m_Mouse;

    static std::unique_ptr<Handler>	m_KeyHandler;
    static std::unique_ptr<Handler>	m_MouseHandler;

    static std::unique_ptr<Renderer>	m_Renderer;
    /// WILL CHANGE ///
    std::shared_ptr<Shader>		m_Shader;
    std::unique_ptr<Texture>		m_Texture;

    std::unique_ptr<VAO>		m_VAO;
    std::unique_ptr<VBO>		m_VBO;
    std::unique_ptr<EBO>		m_EBO;
    /// WILL CHANGE ///
  };
}

#endif // __OPENGL_TEMPLATE_HPP__
