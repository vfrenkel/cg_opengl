
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include "GLScreenCapturer.h"

#include "scene.h"

Scene *SCENE;

void display(void) {
  SCENE->step_and_render();
}

void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);

  // render lights
  // change diffuse to low value once glows are in place.
  float l0_diffuse[4] = { 0.8f, 0.8f, 1.0f, 1.0f };
  float l0_ambient[4] = { 0.0f, 0.0f, 0.4f, 1.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
  float l0_pos[3] = {0.0, 100.0, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);


  glShadeModel(GL_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void key_pressed(unsigned char key, int x, int y) {
  SCENE->key_states[key] = true;
}

void key_up(unsigned char key, int x, int y) {
  SCENE->key_states[key] = false;
}

void mouse_movement(int x, int y) {
  static int prev_x = x;
  static int prev_y = y;

  SCENE->mouse_pos[0] = x;
  SCENE->mouse_pos[1] = y;

  SCENE->mouse_vel[0] = prev_x - x;
  SCENE->mouse_vel[1] = prev_y - y;

  prev_x = x;
  prev_y = y;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(800,800);
  glutInitWindowPosition(100,100);
  glutCreateWindow("CYCLER: Experimental");
  init();
  glewInit();

  SCENE = new Scene();

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);

  glutKeyboardFunc(key_pressed);
  glutKeyboardUpFunc(key_up);

  glutPassiveMotionFunc(mouse_movement);

  glutMainLoop();
  
  return 0;
}
