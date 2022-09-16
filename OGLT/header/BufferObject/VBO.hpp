#ifndef __VBO_HPP__
#define __VBO_HPP__

#include "./BufferObject.hpp"

namespace oglt {
  class VBO final : BufferObject {
  public:
    VBO(void *vertices, GLsizeiptr size);
    VBO();

    void FlushData(void *data, GLsizeiptr size) override;
    void Bind() override;
    void Unbind() override;
    void Delete();
  };
}

#endif // __VBO_HPP__
