#include <Geotree>
#include <igl/viewer/Viewer.h>

int main(int argc, char *argv[])
{
  
  Intersections * I = new Intersections();

  CubeNode * ci1 = new CubeNode(10,10,10);
  CubeNode * ci2 = new CubeNode(10,10,10);
  TranslateNode * ti = new TranslateNode(1,2,3);

  ti->add(ci2);
  ti->build();

  I->add(ci1->g, ti->g);

  I->divide();
  
  //CubeNode cube(10,10,10);

  // CubeNode * c = new CubeNode(1,1,1);
  
  // CubeNode * c1 = new CubeNode(5,3,1);
  // CubeNode * c2 = new CubeNode(10,10,10);
  // TranslateNode * t = new TranslateNode(1,2,3);
  // TranslateNode * t2 = new TranslateNode(-1,-1,-1);
    
  // t->add(c2);
  // t->build();

  // t2->add(c);
  // t2->build();
  
  // c1->g.add(t->g);
  // c1->g.add(t2->g);

  igl::viewer::Viewer viewer;

  //std::cout << c1->g.V << std::endl;
  //std::cout << c1->g.F << std::endl;
  //viewer.data.set_mesh(c1->g.V, c1->g.F);

  //viewer.data.set_mesh(I->CSGUnion.V, I->CSGUnion.F);

  //viewer.data.set_mesh(I->CSGDifference.V, I->CSGDifference.F);

  viewer.data.set_mesh(I->gx.V, I->gx.F);

  viewer.launch();
}
