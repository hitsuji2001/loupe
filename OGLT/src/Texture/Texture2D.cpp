#include "../../header/Texture/Texture2D.hpp"

namespace oglt {
  void Texture2D::CreateTexture(GLint wrapping, GLint filter) {
    glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
  }

  void Texture2D::LoadTexture(const std::string& file_path, GLint format, GLsizei depth) {
    (void) depth;
    int width, height, color_channels;
    unsigned char *data = stbi_load(file_path.c_str(), &width, &height, &color_channels, 0);
    if (data == NULL) {
      std::cerr << "Could not load file `" << file_path << "`" << std::endl;
      exit(1);
    }
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      stbi_image_free(data);
    }

  void Texture2D::ActiveTexture(GLenum index) {
    glActiveTexture(index);
    glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
  }
}
