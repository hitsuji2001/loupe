#include "../../header/BufferObject/EBO.hpp"

namespace oglt {
  EBO::EBO(GLuint *vertices, GLsizeiptr size) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  EBO::EBO() {
    glGenBuffers(1, &this->ID);
  }

  void EBO::FlushData(void *data, GLsizeiptr size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
  }

  void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void EBO::Delete() {
    glDeleteBuffers(1, &this->ID);
  }
}
