#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"


typedef struct hit_record_s {
  point3 p;
  vec3 normal;
  double t;
} HitRec;

int hit(const ray* r, double tmin, double tmax, HitRec* rec);

#endif /* HITTABLE_H */

