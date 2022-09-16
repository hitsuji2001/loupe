#ifndef __TEXTURE_3D_HPP__
#define __TEXTURE_3D_HPP__

#include "./Texture.hpp"

namespace oglt {
  class Texture3D final : public Texture {
  public:
    Texture3D() = default;
    
    void CreateTexture(GLint wrapping = GL_REPEAT, GLint filter = GL_LINEAR) override;
    void LoadTexture(const std::string& file_path, GLint format, GLsizei depth) override;
    void ActiveTexture(GLenum index) override;
  };
}

#endif // __TEXTURE_3D_HPP__
