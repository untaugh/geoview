#include "meshfactory.h"

Mesh *makeCube(float width, float depth, float height, float x, float y, float z)
{
    Mesh* mesh = createMesh(8*2, 12);
    
    mesh->V[0] = x;
    mesh->V[1] = y;
    mesh->V[2] = z;

    mesh->V[6] = x + width;
    mesh->V[7] = y;
    mesh->V[8] = z;

    mesh->V[12] = x;
    mesh->V[13] = y + depth;
    mesh->V[14] = z;

    mesh->V[18] = x + width;
    mesh->V[19] = y + depth;
    mesh->V[20] = z;

    mesh->V[24] = x;
    mesh->V[25] = y;
    mesh->V[26] = z + height;

    mesh->V[30] = x + width;
    mesh->V[31] = y;
    mesh->V[32] = z + height;

    mesh->V[36] = x;
    mesh->V[37] = y + depth;
    mesh->V[38] = z + height;

    mesh->V[42] = x + width;
    mesh->V[43] = y + depth;
    mesh->V[44] = z + height;

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

    return mesh;
}
