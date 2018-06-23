#include "meshfactory.h"

Mesh *makeCube(float width, float depth, float height, float x, float y, float z)
{
    Mesh* mesh = createMesh(24, 12);
    
    mesh->V[0] = x;
    mesh->V[1] = y;
    mesh->V[2] = z;

    mesh->V[6] = x;
    mesh->V[7] = y + depth;
    mesh->V[8] = z;

    mesh->V[12] = x + width;
    mesh->V[13] = y;
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

    
    mesh->V[48] = x;
    mesh->V[49] = y;
    mesh->V[50] = z;

    mesh->V[54] = x + width;
    mesh->V[55] = y;
    mesh->V[56] = z;

    mesh->V[60] = x;
    mesh->V[61] = y;
    mesh->V[62] = z + height;

    mesh->V[66] = x + width;
    mesh->V[67] = y;
    mesh->V[68] = z + height;

    
    mesh->V[72] = x;
    mesh->V[73] = y + depth;
    mesh->V[74] = z;

    mesh->V[78] = x;
    mesh->V[79] = y + depth;
    mesh->V[80] = z + height;

    mesh->V[84] = x + width;
    mesh->V[85] = y + depth;
    mesh->V[86] = z;

    mesh->V[90] = x + width;
    mesh->V[91] = y + depth;
    mesh->V[92] = z + height;

    
    mesh->V[96] = x;
    mesh->V[97] = y;
    mesh->V[98] = z;

    mesh->V[102] = x;
    mesh->V[103] = y;
    mesh->V[104] = z + height;

    mesh->V[108] = x;
    mesh->V[109] = y + depth;
    mesh->V[110] = z;

    mesh->V[114] = x;
    mesh->V[115] = y + depth;
    mesh->V[116] = z + height;

    
    mesh->V[120] = x + width;
    mesh->V[121] = y;
    mesh->V[122] = z;

    mesh->V[126] = x + width;
    mesh->V[127] = y + depth;
    mesh->V[128] = z;

    mesh->V[132] = x + width;
    mesh->V[133] = y;
    mesh->V[134] = z + height;

    mesh->V[138] = x + width;
    mesh->V[139] = y + depth;
    mesh->V[140] = z + height;

    for (int i=0; i<12*3; i++)
    {
	mesh->F[i] = 0;
    }
    
    for (int i=0; i<6; i++)
    {
	mesh->F[0+i*6] = 0 + i*4;
	mesh->F[1+i*6] = 1 + i*4;
	mesh->F[2+i*6] = 2 + i*4;
	
	mesh->F[3+i*6] = 1 + i*4;
	mesh->F[4+i*6] = 3 + i*4;
	mesh->F[5+i*6] = 2 + i*4;
    }

    return mesh;
}
