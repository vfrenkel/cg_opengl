
#include "scene.h"
#include "playercycler.h"


PlayerCycler::PlayerCycler(Scene *scene, std::vector<float> pos, std::vector<double> rot )
  : SceneNode(scene, OBJECT, pos, rot)
{
  // use rotation to calculate initial forward facing direction on the xz plane.
  forward_dir.push_back(0.0L);
  forward_dir.push_back(1.0L);

  this->scene->get_cam()->bind_focus(&(this->pos));
}

void PlayerCycler::step() {
  //TODO: look up real bike dimensions and speeds in meters, m/s.
  // TODO: put these into cycler class as private attributes.
  static float speed = 0.1f;
  double turn_angle_delta = 2.0f;
  double roll_angle_delta = 5.0f;

  this->pos[0] += speed * this->forward_dir[0];
  this->pos[2] += speed * this->forward_dir[1];

  // bleed off speed.
  speed *= 0.98f;
  
  // check for and handle key presses
  if (this->scene->key_states['w']) {
    speed += 0.05f;
  }

  if (this->scene->key_states['a']) {
    if (this->rot[2] > -30.f) {
      this->rot[2] -= roll_angle_delta;
    } else if (this->rot[2] < -30.f && this->rot[2] > -70.f){
      this->rot[2] -= 2.0f / (70.0f - this->rot[2]);
    }

    this->rot[1] += turn_angle_delta;

    double tadr = -turn_angle_delta * PI/180L;
    
    this->forward_dir[0] = this->forward_dir[0] * cos(tadr)
                           - this->forward_dir[1] * sin(tadr);
    this->forward_dir[1] = this->forward_dir[0] * sin(tadr)
                           + this->forward_dir[1] * cos(tadr);
  }

  if (this->scene->key_states['s']) {
    speed -= 0.05f;
  }

  if (this->scene->key_states['d']) {
    if (this->rot[2] < 30.f) {
      this->rot[2] += roll_angle_delta;
    } else if (this->rot[2] > 30.f && this->rot[2] < 70.f){
      this->rot[2] += 2.0f / (70.0f - this->rot[2]);
    }

    this->rot[1] -= turn_angle_delta;

    double tadr = turn_angle_delta * PI/180;
    
    this->forward_dir[0] = this->forward_dir[0] * cos(tadr)
                           - this->forward_dir[1] * sin(tadr);
    this->forward_dir[1] = this->forward_dir[0] * sin(tadr)
                           + this->forward_dir[1] * cos(tadr);
  }
}

void PlayerCycler::render() {
  glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

  // need bike to turn along plane first
  glRotatef(this->rot[1], 0.0, 1.0, 0.0);

  //glRotatef(this->rot[0], 1.0, 0.0, 0.0);
  glRotatef(this->rot[2], 0.0, 0.0, 1.0);
  
  glutSolidCube(2.f);
}


