#ifndef __SCENE_H_
#define __SCENE_H_


#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <math.h>
#include <vector>

#include "camera.h"

#define PI 3.14159265358979323846264338327950288419716939937510L
static const int MAX_DISPLAY_LISTS = 2;

typedef enum {
  OBJECT,
  LIGHT
} SCENE_NODE_TYPE;

typedef enum {
  TEAPOT_DL,
  GRID_PIECE_DL
} DISPLAY_LIST;

class SceneNode;

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
  std::vector<GLuint> display_lists;

public:
  Scene();
  ~Scene();

  bool *key_states;
  std::vector<int> mouse_pos;
  std::vector<int> mouse_vel;

  GLuint *fbo_ids;

  void init_display_lists();

  Camera *get_cam();
  float get_interp_factor();
  GLuint get_display_list(DISPLAY_LIST list);
  void add_node(SceneNode *n);

  void step_and_render();

  void set_cam_target(std::vector<float> *target);
};

class SceneNode {
protected:
  Scene *scene;
  
public:

  SCENE_NODE_TYPE type;
  std::vector<float> pos;
  std::vector<double> rot;

  SceneNode();
  SceneNode( Scene *scene,
	     SCENE_NODE_TYPE type,
	     std::vector<float> pos = std::vector<float>(3,0.0),
	     std::vector<double> rot = std::vector<double>(3,0.0) );
  ~SceneNode();
  
  virtual void step() = 0;
  virtual void render() = 0;
};


class TeapotMesh : public SceneNode {
public:
  float size;

  TeapotMesh( Scene *scene,
	      float size,
	      std::vector<float> pos = std::vector<float>(3,0.0),
	      std::vector<double> rot = std::vector<double>(3,0.0) );

  virtual void step();
  virtual void render();
  
  static GLuint create_display_list();
};

// TODO: abandoned approach, clean up or complete.
class InfinitePlaneMesh : public SceneNode {
public:
  InfinitePlaneMesh();
  virtual void step();
  virtual void render();
};

#endif //__SCENE_H_
