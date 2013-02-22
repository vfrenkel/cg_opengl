#include <math.h>

#include "utils/macros.h"

#include "camera.h"
#include "linalg.h"

Camera::Camera() {
  this->pos = std::vector<float>(3,0.0);
  this->pos.at(1) = 6.0;
  this->pos.at(2) = -10.0;

  this->focus = new std::vector<float>(3,0.0);

  this->up = new std::vector<float>(3,0.0);
  this->up->at(1) = 1.0;

  this->target_dir = new std::vector<double>(2,0.0);
  this->target_dir->at(1) = 1.0;

  this->mouse_pos = NULL;
  this->mouse_vel = NULL;

  this->lag = 12.0;
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
  
  this->mouse_pos = NULL;
  this->mouse_vel = NULL;
  
  this->lag = 12.0;
}

// TODO: add smarter pop logic, and actual deletes...
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

void Camera::step_follow() {
  this->pos[0] = this->focus->at(0) - this->lag * this->target_dir->at(0);
  this->pos[1] = this->focus->at(1) + 5.0;
  this->pos[2] = this->focus->at(2) - this->lag * this->target_dir->at(1);
}

void Camera::step_throw() {
  float dist_to_target = distance3(this->pos, *(this->focus));
  const float threshold = 130.0f;
  
  // throw the camera ahead of bike.
  if (dist_to_target > threshold) {
    this->pos[0] = this->focus->at(0) + threshold * this->target_dir->at(0);
    this->pos[2] = this->focus->at(2) + threshold * this->target_dir->at(1);
  }
}

// check timer, throw camera out ahead of bike.
void Camera::step() {
  step_throw();
}

void Camera::transform_GL() {
//TODO: figure out what is wrong with this->up...
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

void Camera::bind_mouse(std::vector<int> *mouse_pos, std::vector<int> *mouse_vel) {
  this->mouse_pos = mouse_pos;
  this->mouse_vel = mouse_vel;
}
