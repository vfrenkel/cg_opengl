#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <math.h>

#include "scene.h"

#define PI 3.14159265

// sets up a sample scene.
void vf_scene_001(Scene *s) {
  s->get_cam()->pos[0] = 15.0;
  s->get_cam()->pos[1] = 15.0;

  int teapot_pos[3] = {-5.0, 0.0, 0.0};

  s->add_node(new TeapotMesh(s, 2.0f, std::vector<float>(teapot_pos, teapot_pos + 3)));
  s->add_node(new PlayerCycler(s));
}


Scene::Scene() {
  // load up default values.
  this->cam = Camera(0.0, 0.0, -10.0);
  // EXTRA: make this based on actual elapsed time.
  this->interp_factor = 1.0;
  this->key_states = new bool[256];
  
  // EXTRA: make this load from a scene description file.
  vf_scene_001(this);
}

Scene::~Scene() {
  // TODO: pop all nodes off and destroy each one properly.
  
}

Camera *Scene::get_cam() {
  return &(this->cam);
}

float Scene::get_interp_factor() {
  return this->interp_factor;
}

// simple, single interface to add nodes,
// let Scene worry about how to organize the nodes by type.
void Scene::add_node(SceneNode *n) {
  switch (n->type) {
  case OBJECT:
    this->objects.push_back(n);
    break;
  case LIGHT:
    this->lights.push_back(n);
    break;
  // TODO: figure out why outputting to stdout causes seg faults...
  default:
    std::cout << "error: attempted to add node of unknown type to scene" << std::endl;
  }
}

void Scene::step_and_render() {
  glClearColor(0.0,0.0,0.4,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(this->cam.pos[0], this->cam.pos[1], this->cam.pos[2],
	    this->cam.focus[0], this->cam.focus[1], this->cam.focus[2],
	    this->cam.up[0], this->cam.up[1], this->cam.up[2]);

  for (std::vector<SceneNode *>::iterator n = this->objects.begin(); n != this->objects.end(); n++) {
    (*n)->step();

    glPushMatrix();
    (*n)->render();
    glPopMatrix();
  }

  glutSwapBuffers();
}

SceneNode::SceneNode()
  : scene(NULL), type(OBJECT), pos(std::vector<float>(3,0.0)), rot(std::vector<float>(3,0.0))
{ }

SceneNode::~SceneNode() {
  
}

SceneNode::SceneNode( Scene *scene,
		      SCENE_NODE_TYPE type,
		      std::vector<float> pos,
		      std::vector<float> rot )
  : scene(scene), type(type), pos(pos), rot(rot)
{ }

PlayerCycler::PlayerCycler(Scene *scene, std::vector<float> pos, std::vector<float> rot )
  : SceneNode(scene, OBJECT, pos, rot)
{
  // use rotation to calculate initial forward facing direction on the xz plane.
  forward_dir.push_back(0.0);
  forward_dir.push_back(1.0);
}

void PlayerCycler::step() {
  //TODO: calculate new orientation. handle translation separately. forward or backwards along dir vector based on key.
  //TODO: look up real bike dimensions and speeds in meters, m/s.
  // TODO: put these into cycler class as private attributes.
  static float speed = 0.1f;
  float turn_angle_delta = 2.0f;
  float roll_angle_delta = 5.0f;

  float tadr = turn_angle_delta * PI/180;

  this->forward_dir[0] = this->forward_dir[0] * cos(tadr)
                         - this->forward_dir[1] * sin(tadr);
  this->forward_dir[1] = this->forward_dir[0] * sin(tadr)
                         + this->forward_dir[1] * cos(tadr);

  // check for and handle key presses
  if (this->scene->key_states['w']) {
    this->pos[2] += speed;
    
    // TODO: translate 0.1f unit along the direction vector (in - direction).
    if (this->scene->key_states['a']) {
      this->pos[0] += speed;
    } else if (this->scene->key_states['d']) {
      this->pos[0] -= speed;
    }
  }

  if (this->scene->key_states['a']) {
    if (this->rot[2] > -30.f) {
      this->rot[2] -= roll_angle_delta;
    } else if (this->rot[2] < -30.f && this->rot[2] > -70.f){
      this->rot[2] -= 2.0f / (70.0f - this->rot[2]);
    }

    this->rot[1] += turn_angle_delta;
  }

  if (this->scene->key_states['s']) {
    this->pos[2] -= speed;

    if (this->scene->key_states['a']) {
      this->rot[1] += turn_angle_delta;
    } else if (this->scene->key_states['d']) {
      this->rot[1] -= turn_angle_delta;
    }

    // TODO: translate 0.1f unit along the direction vector (in - direction).
    if (this->scene->key_states['a']) {
      this->pos[0] -= 0.1f;
    } else if (this->scene->key_states['d']) {
      this->pos[0] += 0.1f;
    }
  }

  if (this->scene->key_states['d']) {
    if (this->rot[2] < 30.f) {
      this->rot[2] += roll_angle_delta;
    } else if (this->rot[2] > 30.f && this->rot[2] < 70.f){
      this->rot[2] += 2.0f / (70.0f - this->rot[2]);
    }

    this->rot[1] -= turn_angle_delta;
  }
}

void PlayerCycler::render() {
  glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

  // need bike to turn along plane first
  glRotatef(this->rot[1], 0.0, 1.0, 0.0);

  glRotatef(this->rot[0], 1.0, 0.0, 0.0);
  glRotatef(this->rot[2], 0.0, 0.0, 1.0);
  
  glutSolidCube(2.f);
}

TeapotMesh::TeapotMesh( Scene *scene,
		        float size,
		        std::vector<float> pos,
			std::vector<float> rot )
  : SceneNode(scene, OBJECT, pos, rot), size(size)
{ }

void TeapotMesh::step() {
  // TODO: check the keyboard states and transform accordingly.
  
  if (this->rot[0] > 360.0f) {
    this->rot[0] -= 360.0f;
  } else {
    this->rot[0] += 2.0f;
  }

  if (this->rot[1] > 360.0f) {
    this->rot[1] -= 360.0f;
  } else {
    this->rot[1] += 2.0f;
  }

  if (this->rot[2] > 360.0f) {
    this->rot[2] -= 360.0f;
  } else {
    this->rot[2] += 1.0f;
  }
}

void TeapotMesh::render() {
  glTranslatef(this->pos[0], this->pos[1], this->pos[2]);  

  glRotatef(this->rot[0], 1.0, 0.0, 0.0);
  glRotatef(this->rot[1], 0.0, 1.0, 0.0);
  glRotatef(this->rot[2], 0.0, 0.0, 1.0);

  glutSolidTeapot(this->size);
}

CubeMesh::CubeMesh( Scene *scene,
		    float size,
		    std::vector<float> pos,
		    std::vector<float> rot )
  : SceneNode(scene, OBJECT, pos, rot), size(size)
{ }

void CubeMesh::step() {
  // TODO: check the keyboard states and transform accordingly.
  
  // for now, just rotate around z axis.
  if (this->rot[0] > 360.0f) {
    this->rot[0] -= 360.0f;
  } else {
    this->rot[0] += 2.0f;
  }

  if (this->rot[1] > 360.0f) {
    this->rot[1] -= 360.0f;
  } else {
    this->rot[1] += 2.0f;
  }

  if (this->rot[2] > 360.0f) {
    this->rot[2] -= 360.0f;
  } else {
    this->rot[2] += 1.0f;
  }
}

void CubeMesh::render() {
  glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

  glRotatef(this->rot[0], 1.0, 0.0, 0.0);
  glRotatef(this->rot[1], 0.0, 1.0, 0.0);
  glRotatef(this->rot[2], 0.0, 0.0, 1.0);
  
  glutSolidCube(this->size);
}



// TODO: abandoned approach, clean up or complete.
InfinitePlaneMesh::InfinitePlaneMesh() {
  
}

void InfinitePlaneMesh::step() {

}

void InfinitePlaneMesh::render() {
  glBegin(GL_QUADS);
  glVertex4f(1, 0, 1, 0.00001);
  glVertex4f(-1, 0, 1, 0.00001);
  glVertex4f(-1, 0, -1, 0.00001);
  glVertex4f(1, 0, -1, 0.00001);
  glEnd();
}
