#ifndef __SCENE_H_
#define __SCENE_H_

#include <vector>
#include "camera.h"

typedef enum {
  OBJECT,
  LIGHT
} SCENE_NODE_TYPE;

class Scene;

class SceneNode {
protected:
  std::vector<float> pos;
  std::vector<float> rot;
  Scene *scene;
  
public:
  SCENE_NODE_TYPE type;
  SceneNode();
  SceneNode( Scene *scene,
	     SCENE_NODE_TYPE type,
	     std::vector<float> pos = std::vector<float>(3,0.0),
	     std::vector<float> rot = std::vector<float>(3,0.0) );
  ~SceneNode();
  
  virtual void step() = 0;
  virtual void render() = 0;
};

class PlayerCycler : public SceneNode {
private:
  std::vector<float> forward_dir;

public:
  PlayerCycler( Scene *scene,
	        std::vector<float> pos = std::vector<float>(3,0.0),
		std::vector<float> rot = std::vector<float>(3,0.0) );
  virtual void step();
  virtual void render();
};

class TeapotMesh : public SceneNode {
public:
  float size;

  TeapotMesh( Scene *scene,
	      float size,
	      std::vector<float> pos = std::vector<float>(3,0.0),
	      std::vector<float> rot = std::vector<float>(3,0.0) );
  virtual void step();
  virtual void render();
};

class CubeMesh : public SceneNode {
public:
  float size;

  CubeMesh( Scene *scene,
	    float size,
	    std::vector<float> pos = std::vector<float>(3,0.0),
	    std::vector<float> rot = std::vector<float>(3,0.0) );
  virtual void step();
  virtual void render();
};


// TODO: abandoned approach, clean up or complete.
class InfinitePlaneMesh : public SceneNode {
public:
  InfinitePlaneMesh();
  virtual void step();
  virtual void render();
};


/************************************************************
 * Scene Class                                              *
 * stores the current state of the scene, steps and renders *
 * the elements it stores.                                  *
 ************************************************************/
class Scene {
private:
  Camera cam;
  float interp_factor;
  std::vector<SceneNode *> lights;
  std::vector<SceneNode *> objects;

public:
  Scene();
  ~Scene();

  bool *key_states;
  

  Camera *get_cam();
  float get_interp_factor();
  void add_node(SceneNode *n);

  void step_and_render();
};


#endif //__SCENE_H_
