#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

class Shader
{
public:
  Shader();
  GLuint program;
private:
  GLuint vertex;
  GLuint fragment;
  GLuint makeShader(uint32_t shaderType, const char * shaderSource);
};
