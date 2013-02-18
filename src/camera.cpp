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
