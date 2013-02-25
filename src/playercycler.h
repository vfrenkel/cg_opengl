#ifndef __PLAYERCYCLER_H_
#define __PLAYERCYCLER_H_

#include <vector>
#include "model.h"

class PlayerCycler : public SceneNode {
private:
  Model model;
public:
  std::vector<double> forward_dir;

  PlayerCycler( Scene *scene,
	        std::vector<float> pos = std::vector<float>(3,0.0),
		std::vector<double> rot = std::vector<double>(3,0.0) );

  virtual void step();
  virtual void render();

  static GLuint create_display_list();
};


#endif // __PLAYER_CYCLER_H_

