#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace oglt {
  class Shader {
  public:
    GLuint a_ProgramID;

    Shader();
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    virtual ~Shader();

    void Bind();
    void Unbind();

    // Primitive type
    void SetBool(const std::string& name, bool value);
    void SetFloat(const std::string& name, float value);
    void SetInteger(const std::string& name, int value);

    // Vector
    void SetVec2(const std::string& name, float x, float y);
    void SetVec3(const std::string& name, float x, float y, float z);
    void SetVec4(const std::string& name, float x, float y, float z, float w);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);

    // Matrix
    void SetMat2(const std::string& name, const glm::mat2& value);
    void SetMat3(const std::string& name, const glm::mat3& value);
    void SetMat4(const std::string& name, const glm::mat4& value);

    bool LoadShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
  private:
    std::string GetFileContents(const std::string& filePath);
    bool CompileShaderSource(const GLchar *source, GLenum shaderType, GLuint *shader);
    bool CompileShaderFile(const std::string& filePath, GLenum shaderType, GLuint *shader);
    bool LinkProgram(GLuint vertexShader, GLuint fragmentShader);
  };
}

#endif // __SHADER_HPP__
