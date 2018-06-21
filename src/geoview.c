#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "mesh.h"
#include "shader.h"

int finished = 0;

void windowCloseCallback(GLFWwindow *window)
{
	finished = 1;
}

int main(int argc, char **argv)
{
  glfwInit();

  GLFWwindow *window = glfwCreateWindow(640, 480, "geoview", NULL, NULL);

  glfwSetWindowCloseCallback(window, windowCloseCallback);
  
  glfwMakeContextCurrent(window);

  int majorversion;
  int minorversion;
  
  glGetIntegerv(GL_MAJOR_VERSION, &majorversion);
  glGetIntegerv(GL_MINOR_VERSION, &minorversion);

  printf("version: %d.%d\n", majorversion, minorversion);
  
  glClearColor(1.0, 0.0, 0.0, 1.0);

  Mesh* mesh = createMesh();

  mesh->V[0] = 0.0;
  mesh->V[1] = 0.0;
  mesh->V[2] = 0.0;

  mesh->V[3] = 1.0;
  mesh->V[4] = 0.0;
  mesh->V[5] = 0.0;

  mesh->V[6] = 0.0;
  mesh->V[7] = 1.0;
  mesh->V[8] = 0.0;

  mesh->V[9] = 1.0;
  mesh->V[10] = 1.0;
  mesh->V[11] = 0.0;

  mesh->V[12] = 0.0;
  mesh->V[13] = 0.0;
  mesh->V[14] = 1.0;

  mesh->V[15] = 1.0;
  mesh->V[16] = 0.0;
  mesh->V[17] = 1.0;

  mesh->V[18] = 0.0;
  mesh->V[19] = 1.0;
  mesh->V[20] = 1.0;

  mesh->V[21] = 1.0;
  mesh->V[22] = 1.0;
  mesh->V[23] = 1.0;

  mesh->nV = 8;

  mesh->F[0] = 0;
  mesh->F[1] = 1;
  mesh->F[2] = 2;

  mesh->F[3] = 1;
  mesh->F[4] = 2;
  mesh->F[5] = 3;

  mesh->F[6] = 4;
  mesh->F[7] = 5;
  mesh->F[8] = 6;

  mesh->F[9] = 5;
  mesh->F[10] = 6;
  mesh->F[11] = 7;

  mesh->nF = 4;
  
  createProgram();
  
  GLuint VBO;
  GLuint VAO;
  GLuint EBO;

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->nV, mesh->V, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*3*mesh->nF, mesh->F, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  
  while(!finished)
  {
	  glClear(GL_COLOR_BUFFER_BIT);

	  glDrawElements(GL_TRIANGLES, 3*mesh->nF, GL_UNSIGNED_INT, 0);
	  
	  glfwSwapBuffers(window);

	  glfwPollEvents();
  }

  destroyMesh(mesh);
  
  glfwDestroyWindow(window);

  glfwTerminate();

  return 0;
}
