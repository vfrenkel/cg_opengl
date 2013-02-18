#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>

class Camera {
 public:
  std::vector<float> pos;
  std::vector<float> focus;
  std::vector<float> up;

  Camera();
  Camera(float posx, float posy, float posz);
  ~Camera();

  void look_at(std::vector<float> *target);
};


#endif //__CAMERA_H_


