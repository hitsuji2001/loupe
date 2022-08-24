#ifndef __EBO_HPP__
#define __EBO_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO {
public:
  GLuint ID;
  EBO();
  EBO(GLuint *vertices, GLsizeiptr size);

  void Bind();
  void Unbind();
  void Delete();
};

#endif // __EBO_HPP__
