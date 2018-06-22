#include <stdlib.h>
#include "mesh.h"

Mesh *createMesh(uint32_t nV, uint32_t nF)
{
  Mesh *mesh;
  
  mesh = (Mesh*)malloc(sizeof(Mesh));
  mesh->F = (uint32_t*)malloc(sizeof(uint32_t) * nF * 3);
  mesh->V = (float*)malloc(sizeof(float) * nV * 3);
  mesh->nV = nV;
  mesh->nF = nF;

  return mesh;
}

void destroyMesh(Mesh *mesh)
{
  free(mesh->F);
  free(mesh->V);
  free(mesh);
}

void bufferMesh(Mesh *mesh)
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
    
    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->nV, mesh->V, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*3*mesh->nF, mesh->F, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*8, color, GL_STATIC_DRAW);
  
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(1);  
}

void drawMesh(Mesh *mesh)
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, 3*mesh->nF, GL_UNSIGNED_INT, 0);
}
