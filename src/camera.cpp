#include "camera.h"

Camera::Camera() {
  this->pos.push_back(0.0);
  this->pos.push_back(0.0);
  this->pos.push_back(-10.0);

  this->focus.push_back(0.0);
  this->focus.push_back(0.0);
  this->focus.push_back(0.0);

  this->up.push_back(0.0);
  this->up.push_back(1.0);
  this->up.push_back(0.0);
}

Camera::Camera(float posx, float posy, float posz) {
  this->pos.push_back(posx);
  this->pos.push_back(posy);
  this->pos.push_back(posz);

  this->focus.push_back(0.0);
  this->focus.push_back(0.0);
  this->focus.push_back(0.0);

  this->up.push_back(0.0);
  this->up.push_back(1.0);
  this->up.push_back(0.0);
}

Camera::~Camera() {
  this->pos.pop_back();
  this->pos.pop_back();
  this->pos.pop_back();

  this->focus.pop_back();
  this->focus.pop_back();
  this->focus.pop_back();

  this->up.pop_back();
  this->up.pop_back();
  this->up.pop_back();
}

void Camera::look_at(std::vector<float> *target) {
  gluLookAt(this->pos[0], this->pos[1], this->pos[2],
	    (*target)[0], (*target)[1], (*target)[2],
	    this->up[0], this->up[1], this->up[2]);
}
