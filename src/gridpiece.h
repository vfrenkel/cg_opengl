#ifndef __GRIDPIECE_H_
#define __GRIDPIECE_H_

#include <vector>

class GridPiece : public SceneNode {
public:
  GridPiece( Scene *scene,
	     std::vector<float> pos = std::vector<float>(3,0.0),
	     std::vector<double> rot = std::vector<double>(3,0.0) );

  virtual void step();
  virtual void render();

  static GLuint create_display_list();
};

#endif //__GRIDPIECE_H_
