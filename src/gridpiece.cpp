
#include "scene.h"
#include "gridpiece.h"
#include "linalg.h"


GridPiece::GridPiece(Scene *scene, std::vector<float> pos, std::vector<double> rot)
  : SceneNode(scene, OBJECT, pos, rot)
{ }

GLuint GridPiece::create_display_list() {
  const int num_bars = 15;
  const float scale = 10.0f;
  const float bar_scale = 20.0f;

  GLuint list = glGenLists(1);
  glNewList(list, GL_COMPILE);

  glPushMatrix();

  glScalef(scale * bar_scale * num_bars + scale * 2, 1.0f, 1.0f);
  glTranslatef(0.0f, 0.0f, -(scale * num_bars)/2.0f + scale / 2.0f);
  for (unsigned int i = 0; i < num_bars; i++) {
    glutWireSphere(1/bar_scale, 10, 10);
    glTranslatef(0.0f, 0.0f, scale);
  }

  glPopMatrix();

  glPushMatrix();

  glScalef(1.0f, 1.0f, scale * bar_scale * num_bars + scale * 2);
  glTranslatef(-(scale * num_bars)/2.0f + scale / 2.0f, 0.0f, 0.0f);
  for (unsigned int i = 0; i < num_bars; i++) {
    glutWireSphere(1/bar_scale, 10, 10);
    glTranslatef(scale, 0.0f, 0.0f);
  }

  glPopMatrix();

  glEndList();

  return list;
}

void GridPiece::step() {
  
}

void GridPiece::render() {
  glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
  glRotatef(this->rot[0], 1.0, 0.0, 0.0);
  glRotatef(this->rot[1], 0.0, 1.0, 0.0);
  glRotatef(this->rot[2], 0.0, 0.0, 1.0);

  glCallList(this->scene->get_display_list(GRID_PIECE_DL));
}


