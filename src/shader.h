#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#ifndef _SHADER_H_
#define _SHADER_H_

extern const char *vertexSource;
extern const char *fragmentSource;

GLuint createShader(uint32_t shaderType, const char * shaderSource);
GLuint createProgram();

#endif // _SHADER_H_
