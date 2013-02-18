#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <vector>

class Camera {
 public:
  std::vector<float> pos;
  std::vector<float> focus;
  std::vector<float> up;

  Camera();
  Camera(float posx, float posy, float posz);
  ~Camera();
};


#endif //__CAMERA_H_


