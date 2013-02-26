#include "scene.h"
#include "playercycler.h"
#include "gridpiece.h"

// sets up a sample scene.
static void vf_scene_001(Scene *s) {
  float teapot_pos[3] = {-5.0, 0.0, 0.0};
  float player_pos[3] = {0.0, 1.0, 0.0};

  PlayerCycler *player = new PlayerCycler(s, std::vector<float>(player_pos, player_pos+3));
  s->add_node(player);

  // environment setup
  s->add_node(new TeapotMesh(s, 2.0f, std::vector<float>(teapot_pos, teapot_pos + 3)));

  // THE GRID
  s->add_node(new GridPiece(s));

  float grid_W_pos[3] = {0.0, 300.0, 300.0};
  double grid_W_rot[3] = {90.0, 0.0, 0.0};
  s->add_node(new GridPiece(s,
			    std::vector<float>(grid_W_pos, grid_W_pos+3),
			    std::vector<double>(grid_W_rot, grid_W_rot+3)));

  float grid_A_pos[3] = {300.0, 300.0, 0.0};
  float grid_A_rot[3] = {0.0, 0.0, 90.0};
  s->add_node(new GridPiece(s,
			    std::vector<float>(grid_A_pos, grid_A_pos+3),
			    std::vector<double>(grid_A_rot, grid_A_rot+3)));

  s->get_cam()->bind_focus(&(player->pos));
  s->get_cam()->bind_target_dir(&(player->forward_dir));
  s->get_cam()->bind_mouse(&(s->mouse_pos), &(s->mouse_vel));
}

static void init_postproc(Scene *s) {
  s->fbo_ids = new GLuint[1];
  s->rbo_ids = new GLuint[1];
  // first buffer, used for glow model post-processing
  glGenFramebuffers(1, s->fbo_ids);
  glBindFramebuffer(GL_FRAMEBUFFER, s->fbo_ids[0]);

  glGenRenderbuffers(1, s->rbo_ids);
  glBindRenderbuffer(GL_RENDERBUFFER, s->rbo_ids[0]);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA4, 800, 800);
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Scene::Scene() {
  // load up default values.
  this->cam = Camera();
  init_display_lists();
  init_postproc(this);
  // EXTRA: make this based on actual elapsed time.
  this->interp_factor = 1.0;
  this->key_states = new bool[256];
  this->mouse_pos = std::vector<int>(2,0);
  this->mouse_vel = std::vector<int>(2,0);

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
  
  glDeleteFramebuffers(1, this->fbo_ids);
}

void Scene::init_display_lists() {
  this->display_lists.assign(MAX_DISPLAY_LISTS, 0);
  this->display_lists[TEAPOT_DL] = TeapotMesh::create_display_list();
  this->display_lists[GRID_PIECE_DL] = GridPiece::create_display_list();
}

Camera *Scene::get_cam() {
  return &(this->cam);
}

float Scene::get_interp_factor() {
  return this->interp_factor;
}

GLuint Scene::get_display_list(DISPLAY_LIST list) {
  return this->display_lists[list];
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
  //glClearColor(0.01,0.01,0.3,1.0);
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // render camera
  this->cam.step();
  this->cam.transform_GL();

  for (std::vector<SceneNode *>::iterator n = this->objects.begin(); n != this->objects.end(); n++) {
    (*n)->step();

    glPushMatrix();
    (*n)->render();
    glPopMatrix();
  }

  glutSwapBuffers();
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

GLuint TeapotMesh::create_display_list() {
  GLuint list = glGenLists(1);
  glNewList(list, GL_COMPILE);
  glPushMatrix();
  glutSolidTeapot(2.0f);
  glPopMatrix();
  glEndList();
  
  return list;
}

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

  glCallList(this->scene->get_display_list(TEAPOT_DL));
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
