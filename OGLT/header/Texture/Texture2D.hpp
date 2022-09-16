#ifndef __TEXTURE_2D_HPP__
#define __TEXTURE_2D_HPP__

#include "./Texture.hpp"

namespace oglt {
  class Texture2D final : public Texture {
  public:
    Texture2D() = default;
    
    void CreateTexture(GLint wrapping = GL_REPEAT, GLint filter = GL_LINEAR) override;
    void LoadTexture(const std::string& file_path, GLint format, GLsizei depth) override;
    void ActiveTexture(GLenum index) override;
  };
}

#endif // __TEXTURE_2D_HPP__
