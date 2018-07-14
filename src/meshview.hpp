#pragma once
#include "Mesh.h"

using namespace Geotree;

class Meshview
{
public:
  Meshview(Mesh &mesh);
  float *V;
  uint32_t *F;
  uint32_t nV;
  uint32_t nF;
  GLuint VAO;
  void buffer();
  void bufferSimple();
  void draw();
};
