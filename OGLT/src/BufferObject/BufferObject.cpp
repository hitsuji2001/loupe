#include "../../header/BufferObject/BufferObject.hpp"

namespace oglt {
  BufferObject::BufferObject() {
    glGenBuffers(1, &this->ID);
  }

  BufferObject::~BufferObject() {

  }

  void BufferObject::Delete() {
    glDeleteBuffers(1, &this->ID);
  }
}
