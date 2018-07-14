#include "factory.hpp"

Mesh Factory::cube(float x0, float y0, float z0, float x1, float y1, float z1)
{
  Mesh mesh(8, 12);
  
  mesh.V[0] = x0;
  mesh.V[1] = y0;
  mesh.V[2] = z0;

  mesh.V[3] = x0 + x1;
  mesh.V[4] = y0;
  mesh.V[5] = z0;

  mesh.V[6] = x0;
  mesh.V[7] = y0 + y1;
  mesh.V[8] = z0;

  mesh.V[9] = x0 + x1;
  mesh.V[10] = y0 + y1;
  mesh.V[11] = z0;
    
  mesh.V[12] = x0;
  mesh.V[13] = y0;
  mesh.V[14] = z0 + z1;

  mesh.V[15] = x0 + x1;
  mesh.V[16] = y0;
  mesh.V[17] = z0 + z1;

  mesh.V[18] = x0;
  mesh.V[19] = y0 + y1;
  mesh.V[20] = z0 + z1;

  mesh.V[21] = x0 + x1;
  mesh.V[22] = y0 + y1;
  mesh.V[23] = z0 + z1;

  mesh.F[0] = 2;
  mesh.F[1] = 1;
  mesh.F[2] = 0;

  mesh.F[3] = 1;
  mesh.F[4] = 2;
  mesh.F[5] = 3;

  mesh.F[6] = 4;
  mesh.F[7] = 5;
  mesh.F[8] = 6;

  mesh.F[9] = 7;
  mesh.F[10] = 6;
  mesh.F[11] = 5;

  mesh.F[12] = 0;
  mesh.F[13] = 1;
  mesh.F[14] = 4;

  mesh.F[15] = 5;
  mesh.F[16] = 4;
  mesh.F[17] = 1;

  mesh.F[18] = 6;
  mesh.F[19] = 3;
  mesh.F[20] = 2;

  mesh.F[21] = 3;
  mesh.F[22] = 6;
  mesh.F[23] = 7;

  mesh.F[24] = 4;
  mesh.F[25] = 2;
  mesh.F[26] = 0;

  mesh.F[27] = 2;
  mesh.F[28] = 4;
  mesh.F[29] = 6;

  mesh.F[30] = 1;
  mesh.F[31] = 3;
  mesh.F[32] = 5;

  mesh.F[33] = 7;
  mesh.F[34] = 5;
  mesh.F[35] = 3;

  return mesh;
}
