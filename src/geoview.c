#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <cglm/cglm.h>
#include "mesh.h"
#include "shader.h"

int finished = 0;

#define ACTION_DRAG 1
//#define ACTION_DRAG_START 2
#define ACTION_ROTATE 3


static int actionflags = 0;

static int cursor = 0;

static double posx = 0.0;
static double posy = 0.0;

static double rotx = 0.0;
static double roty = 0.0;

static double zoom = 0.0;

static double cursorx = 0.0;
static double cursory = 0.0;

void windowCloseCallback(GLFWwindow *window)
{
	finished = 1;
}

void mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_1)
    {
	if (action == GLFW_PRESS)
	{
	    if (mods == GLFW_MOD_CONTROL)
	    {
		actionflags = ACTION_DRAG;
	    }
	    else
	    {
		actionflags = ACTION_ROTATE;
	    }
	}
	else // GLFW_RELEASE
	{
	    actionflags = 0;
	    cursor = 0;
	}
    }
}

void scrollCallBack(GLFWwindow *window, double x, double y)
{
	zoom += y;
}

void cursorPosCallBack(GLFWwindow *window, double x, double y)
{
	if (actionflags == ACTION_DRAG)
	{
		if (cursor == 0)
		{
			cursor = 1;
		}
		else
		{
			posx += cursorx - x;
			posy += cursory - y;
		}

		cursorx = x;
		cursory = y;
		printf("%f,%f\n", posx, posy);
	}

	if (actionflags == ACTION_ROTATE)
	{
		if (cursor == 0)
		{
			cursor = 1;
		}
		else
		{
			rotx += cursorx - x;
			roty += cursory - y;
		}
		
		cursorx = x;
		cursory = y;
		
		printf("rot: %f,%f\n", rotx, roty);	    
	}
}

void translate(GLfloat transformmatrix[16], double x, double y)
{
	transformmatrix[12] = -x/100;
	transformmatrix[13] = y/100;
	transformmatrix[14] = -0.5;
}

void scale(GLfloat transformmatrix[16], double zoom)
{
	transformmatrix[0] *= zoom/1;
	transformmatrix[5] *= zoom/1;
}

void rotate(GLfloat transformmatrix[16], double x, double y)
{
    transformmatrix[0] = cos(x);
    transformmatrix[2] = -sin(x);
    transformmatrix[8] = sin(x);
    
    transformmatrix[5] = cos(y);
    transformmatrix[6] = sin(y);
    transformmatrix[9] = -sin(y);
    transformmatrix[10] = cos(y) * cos(x);
}

void identity(GLfloat transformmatrix[16])
{
	transformmatrix[0] = 1.0;
	transformmatrix[1] = 0.0;
	transformmatrix[2] = 0.0;
	transformmatrix[3] = 0.0;
	transformmatrix[4] = 0.0;
	transformmatrix[5] = 1.0;
	transformmatrix[6] = 0.0;
	transformmatrix[7] = 0.0;
	transformmatrix[8] = 0.0;
	transformmatrix[9] = 0.0;
	transformmatrix[10] = 1.0;
	transformmatrix[11] = 0.0;
	transformmatrix[12] = 0.0;
	transformmatrix[13] = 0.0;
	transformmatrix[14] = 0.0;
	transformmatrix[15] = 1.0;
}

void ortho(GLfloat transformmatrix[16], double left, double right, double top, double bottom, double near, double far)
{
	transformmatrix[0] = 2.0 / (right - left);
	transformmatrix[1] = 0.0;
	transformmatrix[2] = 0.0;
	transformmatrix[3] = 0.0;
	transformmatrix[4] = 0.0;
	transformmatrix[5] = 2.0 / (top - bottom);
	transformmatrix[6] = 0.0;
	transformmatrix[7] = 0.0;
	transformmatrix[8] = 0.0;
	transformmatrix[9] = 0.0;
	transformmatrix[10] = - 2.0 / (far - near);
	transformmatrix[11] = 0.0;
	transformmatrix[12] = - (right + left) / (right - left);
	transformmatrix[13] = - (top + bottom) / (top - bottom);
	transformmatrix[14] = - (far + near) / (far - near);
	transformmatrix[15] = 1.0;
}

int main(int argc, char **argv)
{
  glfwInit();

  GLFWwindow *window = glfwCreateWindow(640, 480, "geoview", NULL, NULL);

  glfwSetWindowCloseCallback(window, windowCloseCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallBack);
  glfwSetCursorPosCallback(window, cursorPosCallBack);
  glfwSetScrollCallback(window, scrollCallBack);
  
  glfwMakeContextCurrent(window);

  int majorversion;
  int minorversion;
  
  glGetIntegerv(GL_MAJOR_VERSION, &majorversion);
  glGetIntegerv(GL_MINOR_VERSION, &minorversion);

  printf("version: %d.%d\n", majorversion, minorversion);
  
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glEnable(GL_DEPTH_TEST);
  
  Mesh* mesh = createMesh();

  mesh->V[0] = -0.5;
  mesh->V[1] = -0.5;
  mesh->V[2] = -0.5;

  mesh->V[3] = 0.5;
  mesh->V[4] = -0.5;
  mesh->V[5] = -0.5;

  mesh->V[6] = -0.5;
  mesh->V[7] = 0.5;
  mesh->V[8] = -0.5;

  mesh->V[9] = 0.5;
  mesh->V[10] = 0.5;
  mesh->V[11] = -0.5;

  mesh->V[12] = -0.5;
  mesh->V[13] = -0.5;
  mesh->V[14] = 0.5;

  mesh->V[15] = 0.5;
  mesh->V[16] = -0.5;
  mesh->V[17] = 0.5;

  mesh->V[18] = -0.5;
  mesh->V[19] = 0.5;
  mesh->V[20] = 0.5;

  mesh->V[21] = 0.5;
  mesh->V[22] = 0.5;
  mesh->V[23] = 0.5;

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

  
  mesh->F[12] = 0;
  mesh->F[13] = 1;
  mesh->F[14] = 4;

  mesh->F[15] = 1;
  mesh->F[16] = 4;
  mesh->F[17] = 5;

  mesh->F[18] = 2;
  mesh->F[19] = 3;
  mesh->F[20] = 6;

  mesh->F[21] = 3;
  mesh->F[22] = 6;
  mesh->F[23] = 7;

  
  mesh->F[24] = 0;
  mesh->F[25] = 2;
  mesh->F[26] = 4;

  mesh->F[27] = 2;
  mesh->F[28] = 4;
  mesh->F[29] = 6;

  mesh->F[30] = 1;
  mesh->F[31] = 3;
  mesh->F[32] = 5;

  mesh->F[33] = 3;
  mesh->F[34] = 5;
  mesh->F[35] = 7;
  
  mesh->nF = 12;

  float color[32] =
  {
      0.0, 0.0, 0.0, 1.0,
      1.0, 0.0, 0.0, 1.0,
      0.0, 1.0, 0.0, 1.0,
      0.0, 0.0, 1.0, 1.0,

      0.0, 1.0, 1.0, 1.0,
      1.0, 0.0, 1.0, 1.0,
      0.0, 1.0, 1.0, 1.0,
      1.0, 0.0, 1.0, 1.0,
  };
  
      
  
  GLuint program = createProgram();

  GLuint modelLoc = glGetUniformLocation(program, "model");
  GLuint viewLoc = glGetUniformLocation(program, "view");
  GLuint projectionLoc = glGetUniformLocation(program, "projection");

  static GLfloat modelMat[16];
  static GLfloat viewMat[16];
  static GLfloat projectionMat[16];
  
  GLuint VBO;
  GLuint VBO2;
  GLuint VAO;
  GLuint EBO;

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &VBO2);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->nV, mesh->V, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*3*mesh->nF, mesh->F, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*8, color, GL_STATIC_DRAW);
  
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(1);
      
  while(!finished)
  {
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  identity(modelMat);
	  identity(viewMat);
	  identity(projectionMat);
	  ortho(projectionMat, -2,2,2,-2,-10,10);
	  
	  translate(viewMat, posx, posy);
	  //scale(transformmatrix, 1.0);
	  //rotate(modelMat, -rotx/100, -roty/100);

	  glm_rotate_x((float (*)[4])modelMat, -rotx/100, (float (*)[4])modelMat);
	  
	  
	  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMat);
	  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMat);
	  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projectionMat);
	  
	  glDrawElements(GL_TRIANGLES, 3*mesh->nF, GL_UNSIGNED_INT, 0);
	  
	  glfwSwapBuffers(window);

	  glfwPollEvents();
  }

  destroyMesh(mesh);
  
  glfwDestroyWindow(window);

  glfwTerminate();

  return 0;
}
