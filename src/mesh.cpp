#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include "mesh.hpp"

Mesh::Mesh(uint32_t nV, uint32_t nF)
{
  std::cout << "Mesh " << nV << " " << nF << std::endl;
  F = (uint32_t*)malloc(sizeof(uint32_t) * nF * 3);
  V = (float*)malloc(sizeof(float) * nV * 3);
  this->nV = nV;
  this->nF = nF;
}

Mesh::~Mesh()
{
  free(F);
  free(V);
}
