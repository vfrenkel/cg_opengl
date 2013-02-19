#ifndef __PLAYERCYCLER_H_
#define __PLAYERCYCLER_H_

#include <vector>

class PlayerCycler : public SceneNode {
public:
  std::vector<double> forward_dir;

  PlayerCycler( Scene *scene,
	        std::vector<float> pos = std::vector<float>(3,0.0),
		std::vector<double> rot = std::vector<double>(3,0.0) );
  virtual void step();
  virtual void render();
};


#endif // __PLAYER_CYCLER_H_

