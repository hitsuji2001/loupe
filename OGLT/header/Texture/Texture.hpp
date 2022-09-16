#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../stb/stb_image.h"

namespace oglt {
  enum class TextureType {
    TextureType2D,
    TextureType3D,
  };

  class Texture {
  public:
    Texture();
    virtual ~Texture();

    virtual void CreateTexture(GLint wrapping = GL_REPEAT, GLint filter = GL_LINEAR) = 0;
    virtual void ActiveTexture(GLenum index) = 0;
    virtual void LoadTexture(const std::string& filePath, GLint format, GLsizei depth = 16) = 0;

  public:
    GLuint m_TextureID;
    GLenum m_Target;
  };
}

#endif // __TEXTURE_HPP__
