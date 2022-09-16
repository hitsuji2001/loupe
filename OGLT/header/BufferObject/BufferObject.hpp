#ifndef __BUFFER_OBJECT_HPP
#define __BUFFER_OBJECT_HPP

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace oglt {
  class BufferObject {
  public:
    GLuint ID;

    BufferObject();
    virtual ~BufferObject();

    virtual void FlushData(void *data, GLsizeiptr size) = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    void Delete();
  };
}

#endif // __BUFFER_OBJECT_HPP
