#include "utils/macros.h"

#include "camera.h"

Camera::Camera() {
  this->pos = std::vector<float>(3,0.0);
  this->pos.at(2) = -10.0;

  this->focus = new std::vector<float>(3,0.0);

  this->up = new std::vector<float>(3,0.0);
  this->up->at(1) = 1.0;

  this->target_dir = new std::vector<double>(2,0.0);
  this->target_dir->at(1) = 1.0;

  this->lag = 6.0;
}

Camera::Camera(float posx, float posy, float posz) {
  this->pos.push_back(posx);
  this->pos.push_back(posy);
  this->pos.push_back(posz);

  this->focus = new std::vector<float>(3, 0.0);

  this->up = new std::vector<float>(3,0.0);
  this->up->at(1) = 1.0;

  this->target_dir = new std::vector<double>(2,0.0);
  this->target_dir->at(1) = 1.0;
  
  this->lag = 6.0;
}

Camera::~Camera() {
  this->pos.pop_back();
  this->pos.pop_back();
  this->pos.pop_back();

  this->focus->pop_back();
  this->focus->pop_back();
  this->focus->pop_back();
  //SAFE_DELETE(this->focus);

  this->up->pop_back();
  this->up->pop_back();
  this->up->pop_back();
  //SAFE_DELETE(this->up);

  this->target_dir->pop_back();
  this->target_dir->pop_back();
  //SAFE_DELETE(this->target_dir);
}

//TODO: update position to be based on focus, lag, target_dir like in the translate, so glu lookat will work correctly!
void Camera::step() {
  // * this->target_dir->at(0)
  this->pos[0] = this->focus->at(0) - this->lag * this->target_dir->at(0);
  this->pos[1] = this->focus->at(1);
  this->pos[2] = this->focus->at(2) - this->lag * this->target_dir->at(1);
}

void Camera::transform_GL() {
  // move the camera into position above and behind the object.
  glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
  

//TODO: figure out what is wrong with this->up...
  // gluLookAt(this->pos.at(0), this->pos.at(1), this->pos.at(2),
  // 	    this->focus->at(0), this->focus->at(1), this->focus->at(2),
  //  	    this->up->at(0), this->up->at(1), this->up->at(2));

  gluLookAt(this->pos.at(0), this->pos.at(1), this->pos.at(2),
  	    this->focus->at(0), this->focus->at(1), this->focus->at(2),
  	    0.0, 1.0, 0.0);
}
void Camera::bind_focus(std::vector<float> *target) {
  this->focus = target;
}

void Camera::bind_up(std::vector<float> *up) {
  this->up = up;
}

void Camera::bind_target_dir(std::vector<double> *target_dir) {
  this->target_dir = target_dir;
}
