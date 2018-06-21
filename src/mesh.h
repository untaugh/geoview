#include <stdint.h>

typedef struct _MESH_
{
  float *V;
  uint32_t *F;
  uint32_t nV;
  uint32_t nF;
} Mesh;


Mesh *createMesh();
void destroyMesh(Mesh *mesh);
void drawMesh(Mesh *mesh);
