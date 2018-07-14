#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "meshview.hpp"

Meshview::Meshview(Mesh &mesh)
{
  uint32_t numfaces = mesh.numFaces();
  uint32_t numverts = numfaces * 3 * 2;

  F = (uint32_t*) malloc(sizeof(uint32_t) * numfaces * 3);
  V = (float*) malloc(sizeof(float) * numverts * 3);

  this->nV = numverts;
  this->nF = numfaces;

  for(uint32_t i=0; i<numfaces; i++)
    {
      for (uint32_t p=0; p<3; p++)
	{
	  uint32_t facevertex = i*3 + p;

	  F[facevertex] = facevertex;

	  int face = mesh.F.row(i)[p];

	  float v0 = mesh.V.row(face)[0];
	  float v1 = mesh.V.row(face)[1];
	  float v2 = mesh.V.row(face)[2];

	  V[facevertex * 3*2 + 0] = v0;
	  V[facevertex * 3*2 + 1] = v1;
	  V[facevertex * 3*2 + 2] = v2;
	}
    }
}

void Meshview::bufferSimple()
{
  GLuint VBO;
  GLuint EBO;
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    uint32_t e[] = {0,1,2};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*3, e, GL_STATIC_DRAW);

    float v[] = {0,0,0, 1,0,0, 0,1,0};
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, v, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
}

void Meshview::buffer()
{
    GLuint VBO;
    GLuint VBO2;
    GLuint EBO;

    float color[32] =
	{
	    1.0, 1.0, 0.0, 1.0,
	    1.0, 0.0, 0.0, 1.0,
	    0.0, 1.0, 0.0, 1.0,
	    0.0, 0.0, 1.0, 1.0,

	    0.0, 1.0, 1.0, 1.0,
	    1.0, 0.0, 1.0, 1.0,
	    0.0, 1.0, 1.0, 1.0,
	    1.0, 0.0, 1.0, 1.0,
	};

    for (uint32_t i=0; i<nF; i++)
    {
	int v0 = F[0+i*3];
	int v1 = F[1+i*3];
	int v2 = F[2+i*3];

	glm::vec3 cross;

	glm::vec3 a = { V[v0*3*2+0], V[v0*3*2+1], V[v0*3*2+2]};
	glm::vec3 b = { V[v1*3*2+0], V[v1*3*2+1], V[v1*3*2+2]};
	glm::vec3 c = { V[v2*3*2+0], V[v2*3*2+1], V[v2*3*2+2]};
	glm::vec3 d;
	glm::vec3 e;

	d = a - b;
	e = a - c;

	cross = glm::normalize(glm::cross(d,e));
	
    	V[3+v0*3*2] = cross[0];
    	V[4+v0*3*2] = cross[1];
    	V[5+v0*3*2] = cross[2];

	V[3+v1*3*2] = cross[0];
    	V[4+v1*3*2] = cross[1];
    	V[5+v1*3*2] = cross[2];

	V[3+v2*3*2] = cross[0];
    	V[4+v2*3*2] = cross[1];
    	V[5+v2*3*2] = cross[2];
    }

    for (int i=0; i<32; i++)
      {
	std::cout << V[i] << std::endl;
      }
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*3*nF, F, GL_STATIC_DRAW);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*2*nV, V, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*8, color, GL_STATIC_DRAW);
  
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(2);  
}

void Meshview::draw()
{
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 3*nF, GL_UNSIGNED_INT, 0);
  //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
}
