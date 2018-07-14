#pragma once
#include "mesh.hpp"

class Meshview
{
public:
  Meshview(Mesh &mesh);
  Mesh *viewmesh;
  GLuint VAO;
  void buffer();
  void bufferSimple();
  void draw();
private:

};
