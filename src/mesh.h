#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <stdint.h>

#ifndef _MESH_H_
#define _MESH_H_

typedef struct _MESH_
{
    float *V;
    uint32_t *F;
    uint32_t nV;
    uint32_t nF;
    GLuint VAO;
} Mesh;

Mesh *createMesh(uint32_t nV, uint32_t nF);
void destroyMesh(Mesh *mesh);
void bufferMesh(Mesh *mesh);
void drawMesh(Mesh *mesh);

#endif // _MESH_H_
