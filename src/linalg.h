#ifndef __LINALG_H_
#define __LINALG_H_

#include <math.h>

void normalize2L(std::vector<double> &v) {
  double norm = sqrt(v[0] * v[0] + v[1] * v[1]);

  v[0] = v[0] / norm;
  v[1] = v[1] / norm;
}


#endif //__LINALG_H_
