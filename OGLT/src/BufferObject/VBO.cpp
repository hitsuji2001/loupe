#include "../../header/BufferObject/VBO.hpp"

namespace oglt {
  VBO::VBO(void *vertices, GLsizeiptr size) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  VBO::VBO() {
    glGenBuffers(1, &this->ID);
  }

  void VBO::FlushData(void *data, GLsizeiptr size) {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
  }

  void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void VBO::Delete() {
    glDeleteBuffers(1, &this->ID);
  }
}
