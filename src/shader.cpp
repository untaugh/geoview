#include <iostream>
#include "shader.hpp"

const char *vertexSourceSimple = "#version 130\n"
  "in vec3 pos;\n"
  "in vec3 normal;\n"
  "out vec4 outColor;\n"
  "out vec3 outNormal;\n"
  "out vec3 outFrag;\n"
  "uniform mat4 model;\n"
  "uniform mat4 normalMat;\n"
  "uniform mat4 view;\n"
  "uniform mat4 projection;\n"
  "void main(){\n"
  "gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);\n"
  "outColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
  "outFrag = vec3(model * vec4(pos.x, pos.y, pos.z, 1.0));\n"
  "outNormal = vec3(normalMat * vec4(normal.x, normal.y, normal.z, 1.0));\n"
  "}\n\0";

const char *vertexSource = "#version 130\n"
    "in vec3 pos;\n"
    "in vec3 normal;\n"
    "in vec4 color;\n"
    "out vec4 outColor;\n"
    "out vec3 outNormal;\n"
    "out vec3 outFrag;\n"
    "uniform mat4 model;\n"
    "uniform mat4 normalMat;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main(){\n"
    "gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "outColor = color;\n"
    "outFrag = vec3(model * vec4(pos.x, pos.y, pos.z, 1.0));\n"
    "outNormal = vec3(normalMat * vec4(normal.x, normal.y, normal.z, 1.0));\n"
    //"outNormal = mat3(inverse(model)) * normal;\n"
    "}\n\0";

const char *fragmentSourceSimple = "#version 130\n"
  "out vec4 FragColor;\n"
  "in vec4 outColor;\n"
  "in vec3 outNormal;\n"
  "in vec3 outFrag;\n"
  "uniform vec3 lightPos;\n"
  "void main(){\n"
  "FragColor = outColor;\n"
  "}\n\0";

const char *fragmentSource = "#version 130\n"
  "out vec4 FragColor;\n"
  "in vec4 outColor;\n"
  "in vec3 outNormal;\n"
  "in vec3 outFrag;\n"
  "uniform vec3 lightPos;\n"
  "void main(){\n"
  "vec3 norm = normalize(outNormal);\n"
  "vec3 lightDir = normalize(lightPos - outFrag);\n"
  "float diff = max(dot(norm, lightDir), 0.0);\n"
  "vec4 diffuse = diff * vec4(1,1,1,1);\n"
  //"vec4 result = (diffuse + 0.25) * outColor;\n"
  "vec4 result = (diffuse + 0.25) * vec4(1,1,0,1);\n"
  "FragColor = vec4(result);\n"
  "}\n\0";

Shader::Shader()
{
  vertex = makeShader(GL_VERTEX_SHADER, vertexSourceSimple);
  fragment = makeShader(GL_FRAGMENT_SHADER, fragmentSource);
  program = glCreateProgram();
  
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  glLinkProgram(program);
  glUseProgram(program);  
}

GLuint Shader::makeShader(uint32_t shaderType, const char * shaderSource)
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
      std::cout << "Error:" << infoLog << std::endl;
    }

  return shader;  
}
