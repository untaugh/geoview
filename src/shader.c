#include "shader.h"
#include <stdio.h>

const char *vertexSource = "#version 130\n"
  "in vec3 pos;\n"
  "void main(){ gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); }\n\0";

const char *fragmentSource = "#version 130\n"
  "out vec4 FragColor;\n"
  "void main(){ FragColor=vec4(0.0,1.0,0.0,1.0); }\n\0";

GLuint createShader(uint32_t shaderType, const char * shaderSource)
{
  GLuint shader = glCreateShader(shaderType);
  
  glShaderSource(shader, 1, &shaderSource, NULL);

  glCompileShader(shader);

  int  success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if(!success)
    {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      printf("Error: %s\n", infoLog);
    }

  return shader;
}

GLuint createProgram()
{
  GLuint vertex = createShader(GL_VERTEX_SHADER, vertexSource);
  GLuint fragment = createShader(GL_FRAGMENT_SHADER, fragmentSource);
  GLuint program = glCreateProgram();

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  glLinkProgram(program);
  glUseProgram(program);

  return program;
}