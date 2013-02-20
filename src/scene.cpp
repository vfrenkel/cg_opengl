#include "scene.h"
#include "playercycler.h"

// sets up a sample scene.
void vf_scene_001(Scene *s) {
  int teapot_pos[3] = {-5.0, 0.0, 0.0};

  s->add_node(new TeapotMesh(s, 2.0f, std::vector<float>(teapot_pos, teapot_pos + 3)));
  PlayerCycler *player = new PlayerCycler(s);
  s->add_node(player);

  s->get_cam()->bind_focus(&(player->pos));
  s->get_cam()->bind_target_dir(&(player->forward_dir));
}


Scene::Scene() {
  // load up default values.
  this->cam = Camera();
  // EXTRA: make this based on actual elapsed time.
  this->interp_factor = 1.0;
  this->key_states = new bool[256];

  // clear all key states.
  for (int i = 0; i < 256; i++) {
    this->key_states[i] = false;
  }
  
  // EXTRA: make this load from a scene description file.
  // load scene.
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

  //glPushMatrix();
  this->cam.step();
  this->cam.transform_GL();

  for (std::vector<SceneNode *>::iterator n = this->objects.begin(); n != this->objects.end(); n++) {
    (*n)->step();

    glPushMatrix();
    (*n)->render();
    glPopMatrix();
  }

  glutSwapBuffers();

  //glPopMatrix();
}

SceneNode::SceneNode()
  : scene(NULL), type(OBJECT), pos(std::vector<float>(3,0.0)), rot(std::vector<double>(3,0.0))
{ }

SceneNode::~SceneNode() {
  
}

SceneNode::SceneNode( Scene *scene,
		      SCENE_NODE_TYPE type,
		      std::vector<float> pos,
		      std::vector<double> rot )
  : scene(scene), type(type), pos(pos), rot(rot)
{ }

TeapotMesh::TeapotMesh( Scene *scene,
		        float size,
		        std::vector<float> pos,
			std::vector<double> rot )
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
		    std::vector<double> rot )
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
