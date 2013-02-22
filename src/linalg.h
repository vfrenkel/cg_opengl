#ifndef __LINALG_H_
#define __LINALG_H_

#include <math.h>

static void normalize2L(std::vector<double> &v) {
  double norm = sqrt(v[0] * v[0] + v[1] * v[1]);

  v[0] = v[0] / norm;
  v[1] = v[1] / norm;
}

static float distance3(std::vector<float> &a, std::vector<float> &b) {
  float x = b[0] - a[0];
  float y = b[1] - a[1];
  float z = b[2] - a[2];
  return (sqrt(x*x + y*y + z*z));
}

static void _tbPointToVector(int x, int y, int width, int height, std::vector<float> &v)
{
  float d, a;

  /* project x, y onto a hemi-sphere centered within width, height. */
  v[0] = (2.0 * x - width) / width;
  v[1] = (height - 2.0 * y) / height;
  d = sqrt(v[0] * v[0] + v[1] * v[1]);
  v[2] = cos((3.14159265 / 2.0) * ((d < 1.0) ? d : 1.0));
  a = 1.0 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] *= a;
  v[1] *= a;
  v[2] *= a;
}

#endif //__LINALG_H_
