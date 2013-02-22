#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>

class Camera {
 private:
  std::vector<float> pos;
  std::vector<float> *focus;
  std::vector<float> *up;
  std::vector<double> *target_dir;
  std::vector<int> *mouse_pos;
  std::vector<int> *mouse_vel;
  float lag;

  void step_follow();
  void step_throw();

 public:

  Camera();
  Camera(float posx, float posy, float posz);
  ~Camera();

  void bind_focus(std::vector<float> *target);
  void bind_up(std::vector<float> *up);
  void bind_target_dir(std::vector<double> *target_dir);
  void bind_mouse(std::vector<int> *mouse_pos, std::vector<int> *mouse_vel);

  void step();
  void transform_GL();
};


#endif //__CAMERA_H_


