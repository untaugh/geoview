#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <cglm/cglm.h>
#include "mesh.h"
#include "meshfactory.h"
#include "shader.h"

int finished = 0;

#define ACTION_BEGIN 0x1
#define ACTION_DRAG 0x2
#define ACTION_ROTATE 0x4

static int actionflags = 0;

static double posx = 0.0;
static double posy = 0.0;

static double rotx = 0.0;
static double roty = 0.0;

static double zoom = 1.0;

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
	}
    }
}

void scrollCallBack(GLFWwindow *window, double x, double y)
{
    zoom += y;

    if (zoom < 1.0) zoom = 1.0;
}

void cursorPosCallBack(GLFWwindow *window, double x, double y)
{
    if ((actionflags & ACTION_DRAG) != 0)
    {
	if ((actionflags & ACTION_BEGIN) == 0)
	{
	    actionflags |= ACTION_BEGIN;
	}
	else
	{
	    posx += cursorx - x;
	    posy += cursory - y;
	}

	cursorx = x;
	cursory = y;
    }

    if ((actionflags & ACTION_ROTATE) != 0)
    {
	if ((actionflags & ACTION_BEGIN) == 0)
	{
	    actionflags |= ACTION_BEGIN;
	}
	else
	{
	    rotx += cursorx - x;
	    roty += cursory - y;
	}
	
	cursorx = x;
	cursory = y;
    }
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
  
  Mesh* mesh = makeCube(1,1,1,0,0,0);
  Mesh* mesh2 = makeCube(1,1,1,1,1,1);
  Mesh* mesh3 = makeCube(1,1,1,1,0.5,0);
  
  GLuint program = createProgram();

  GLuint modelLoc = glGetUniformLocation(program, "model");
  GLuint viewLoc = glGetUniformLocation(program, "view");
  GLuint projectionLoc = glGetUniformLocation(program, "projection");

  mat4 modelMat;
  mat4 viewMat;
  mat4 projectionMat;

  bufferMesh(mesh);
  bufferMesh(mesh2);
  bufferMesh(mesh3);
  
  while(!finished)
  {
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  glm_mat4_identity(modelMat);
	  
	  vec3 aabb[2] = { {-zoom, -zoom, -1000}, {zoom, zoom, 1000} };
	  
	  glm_ortho_aabb(aabb, projectionMat);

	  vec3 eye = {0.0, -1.0, 0.0};
	  vec3 center = {0.0, 0.0, 0.0};
	  vec3 up = {0.0, 0.0, 1.0};

	  glm_lookat(eye, center, up, viewMat);

	  glm_translate_x(viewMat, -posx/100);
	  glm_translate_z(viewMat, posy/100);

	  glm_rotate_z(modelMat, -rotx/100, modelMat);
	  glm_rotate_x(modelMat, -roty/100, modelMat);
	  
	  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)modelMat);
	  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)viewMat);
	  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float*)projectionMat);

	  drawMesh(mesh);
	  drawMesh(mesh2);
	  drawMesh(mesh3);
	  
	  glfwSwapBuffers(window);

	  glfwPollEvents();
  }

  destroyMesh(mesh);
  destroyMesh(mesh2);
  
  glfwDestroyWindow(window);

  glfwTerminate();

  return 0;
}
