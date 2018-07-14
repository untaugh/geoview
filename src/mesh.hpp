#pragma once

#include <stdint.h>

class Mesh
{
public:
  Mesh(uint32_t nV, uint32_t nF);
  ~Mesh();
  float *V;
  uint32_t *F;
  uint32_t nV;
  uint32_t nF;
};
