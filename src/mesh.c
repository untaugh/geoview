#include <stdlib.h>
#include <cglm/cglm.h>
#include "mesh.h"

Mesh *createMesh(uint32_t nV, uint32_t nF)
{
  Mesh *mesh;
  
  mesh = (Mesh*)malloc(sizeof(Mesh));
  mesh->F = (uint32_t*)malloc(sizeof(uint32_t) * nF * 3);
  mesh->V = (float*)malloc(sizeof(float) * nV * 3 * 2);
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

    for (int i=0; i<mesh->nF; i++)
    {
	int v0 = mesh->F[0+i*3];
	int v1 = mesh->F[1+i*3];
	int v2 = mesh->F[2+i*3];
	
	vec3 cross;

	vec3 a = { mesh->V[v0*3*2+0], mesh->V[v0*3*2+1], mesh->V[v0*3*2+2]};
	vec3 b = { mesh->V[v1*3*2+0], mesh->V[v1*3*2+1], mesh->V[v1*3*2+2]};
	vec3 c = { mesh->V[v2*3*2+0], mesh->V[v2*3*2+1], mesh->V[v2*3*2+2]};
	vec3 d;
	vec3 e;

	glm_vec_sub(a,b,d);
	glm_vec_sub(a,c,e);
	
	glm_vec_cross(d, e, cross);

	glm_vec_normalize(cross);

	printf("%d, %d, %d\n", v0, v1, v2);
	
	glm_vec3_print(d, stdout);
	glm_vec3_print(e, stdout);
	glm_vec3_print(cross, stdout);
	
    	mesh->V[3+v0*3*2] = cross[0];
    	mesh->V[4+v0*3*2] = cross[1];
    	mesh->V[5+v0*3*2] = cross[2];

	mesh->V[3+v1*3*2] = cross[0];
    	mesh->V[4+v1*3*2] = cross[1];
    	mesh->V[5+v1*3*2] = cross[2];

	mesh->V[3+v2*3*2] = cross[0];
    	mesh->V[4+v2*3*2] = cross[1];
    	mesh->V[5+v2*3*2] = cross[2];
    }
    
    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*3*mesh->nF, mesh->F, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*2*mesh->nV, mesh->V, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*8, color, GL_STATIC_DRAW);
  
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(2);
}

void drawMesh(Mesh *mesh)
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, 3*mesh->nF, GL_UNSIGNED_INT, 0);
}
