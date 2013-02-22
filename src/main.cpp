
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

  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
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
