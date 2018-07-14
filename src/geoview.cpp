#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "MeshFactory.h"

#include "geoview.hpp"
#include "shader.hpp"
#include "meshview.hpp"

Geoview* Geoview::geoview;

Geoview::Geoview()
{
}

Geoview::~Geoview()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

uint32_t Geoview::init()
{
  this->geoview = this;

  glfwInit();

  window = glfwCreateWindow(640, 480, "geoview", NULL, NULL);

  glfwSetWindowUserPointer(window, this);

  glfwSetWindowCloseCallback(window, windowCloseCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallBack);
  glfwSetCursorPosCallback(window, cursorPosCallBack);
  glfwSetScrollCallback(window, scrollCallBack);

  glfwMakeContextCurrent(window);

  glClearColor(0.3, 0.3, 0.3, 1.0);
  glEnable(GL_DEPTH_TEST);
  
  return 0;
}

uint32_t Geoview::run()
{
  MeshFactory factory;

  Mesh cube0 = factory.cube(1,1,1);
  Mesh cube1 = factory.cube(1,1,1);

  cube1.translate(Eigen::Vector3d(1,1,1));
  
  Meshview view0(cube0);
  Meshview view1(cube1);
  
  Shader shader;

  GLuint modelLoc = glGetUniformLocation(shader.program, "model");
  GLuint viewLoc = glGetUniformLocation(shader.program, "view");
  GLuint projectionLoc = glGetUniformLocation(shader.program, "projection");
  GLuint lightLoc = glGetUniformLocation(shader.program, "lightPos");
  GLuint normalMatLoc = glGetUniformLocation(shader.program, "normalMat");

  glm::vec3 light = {0, -10, 0};

  glUniform3fv(lightLoc, 1, glm::value_ptr(light));

  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projectionMat;
  glm::mat4 normalMat;

  view0.buffer();
  view1.buffer();

  while(!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      modelMat = glm::mat4();

      projectionMat = glm::ortho(-zoom, zoom, -zoom, zoom, -1000.f, 1000.f);

      glm::vec3 eye(0.0, -10.0, 0.0);
      glm::vec3 center(0.0, 0.0, 0.0);
      glm::vec3 up(0.0, 0.0, 1.0);

      viewMat = glm::lookAt(eye, center, up);

      viewMat = glm::translate(viewMat, glm::vec3(-posx/100.0f, 0.0f, posy/100.0f));

      modelMat = glm::rotate(modelMat, (float)-rotx/100.0f, glm::vec3(0.0f, 0.0f, 1.0f));
      modelMat = glm::rotate(modelMat, (float)-roty/100.0f, glm::vec3(1.0f, 0.0f, 0.0f));

      normalMat = glm::inverse(modelMat);

      normalMat = glm::transpose(normalMat);

      glUniformMatrix4fv(normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMat));
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
      glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
      
      view0.draw();
      view1.draw();
	  
      glfwSwapBuffers(window);

      glfwPollEvents();
    }

  return 0;
}

void Geoview::windowCloseCallback(GLFWwindow *window)
{
}

void Geoview::mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_1)
    {
      if (action == GLFW_PRESS)
    	{
	  if (mods == GLFW_MOD_CONTROL)
    	    {
	      geoview->actionflags = ACTION_DRAG;
    	    }
	  else
    	    {
	      geoview->actionflags = ACTION_ROTATE;
    	    }
    	}
      else // GLFW_RELEASE
    	{
	  geoview->actionflags = 0;
    	}
    }
}
void Geoview::scrollCallBack(GLFWwindow *window, double x, double y)
{
  geoview->zoom -= y;

  if (geoview->zoom < 1.0)
    {
      geoview->zoom = 1.0;
    }
}

void Geoview::cursorPosCallBack(GLFWwindow *window, double x, double y)
{
  if ((geoview->actionflags & ACTION_DRAG) != 0)
    {
      if ((geoview->actionflags & ACTION_BEGIN) == 0)
	{
	  geoview->actionflags |= ACTION_BEGIN;
	}
      else
	{
	  geoview->posx += geoview->cursorx - x;
	  geoview->posy += geoview->cursory - y;
	}

      geoview->cursorx = x;
      geoview->cursory = y;
    }

  if ((geoview->actionflags & ACTION_ROTATE) != 0)
    {
      if ((geoview->actionflags & ACTION_BEGIN) == 0)
	{
	  geoview->actionflags |= ACTION_BEGIN;
	}
      else
	{
	  geoview->rotx += geoview->cursorx - x;
	  geoview->roty += geoview->cursory - y;
	}

      geoview->cursorx = x;
      geoview->cursory = y;
    }
}

int main()
{
  Geoview app;

  app.init();
  return app.run();
}
