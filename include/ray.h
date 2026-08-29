#ifndef RAY_H

#include "vec3.h"


typedef struct ray_s {
  point3 orig;
  vec3 dir;
} ray;

point3 ray_at(ray ray, double t) {
  return addVec(ray.orig, multVecBy(ray.dir, t));
}

#endif /* RAY_H */

