
#include "scene.h"
#include "gridpiece.h"
#include "linalg.h"


GridPiece::GridPiece(Scene *scene, std::vector<float> pos, std::vector<double> rot)
  : SceneNode(scene, OBJECT, pos, rot)
{ }

GLuint GridPiece::create_display_list() {
  const int num_bars = 60;
  const float spacing = 10.0f;
  
  GLfloat red_emissive_material[] = {1.0, 0.0, 0.0};
  GLfloat black_out_material[] = {0.0, 0.0, 0.0};

  GLuint list = glGenLists(1);
  glNewList(list, GL_COMPILE);

  glPushMatrix();
  //glPushAttrib(GL_MATERIAL);
  glTranslatef(-num_bars*spacing/2.0,0.0,-num_bars*spacing/2.0);

  glBegin(GL_LINES);
  for (unsigned int i = 0; i < num_bars; i++) {
    if (i == 0) { 
      //glColor3f(1.0, 0.0, 0.0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, red_emissive_material);
    } else {
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black_out_material);
      //glColor3f(0.0, 0.0, 0.4);
    }
    glVertex3f(spacing*i,0,0);
    glVertex3f(spacing*i,0,spacing*num_bars);
    glVertex3f(0,0,spacing*i);
    glVertex3f(spacing*num_bars,0,spacing*i);
  }
  glEnd();

  //glPopAttrib();
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


