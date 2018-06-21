#include <stdlib.h>
#include "mesh.h"

Mesh *createMesh()
{
  uint32_t size = 100 * 3;
  Mesh *mesh;
  
  mesh = (Mesh*)malloc(sizeof(Mesh));
  mesh->F = (uint32_t*)malloc(sizeof(uint32_t) * size);
  mesh->V = (float*)malloc(sizeof(float) * size * 3);
  mesh->nV = 0;
  mesh->nF = 0;

  return mesh;
}

void destroyMesh(Mesh *mesh)
{
  free(mesh->F);
  free(mesh->V);
  free(mesh);
}

void drawMesh(Mesh *mesh)
{
  
}
