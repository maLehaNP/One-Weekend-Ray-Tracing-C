#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <stdlib.h>

/* Constants */

const double infinity = DBL_MAX;
const double pi = 3.1415926535897932385;

/* Utility Functions */

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double random_double() {
  /* Random real in [0, 1) */
  return rand() / (RAND_MAX + 1.);
}

double random_double_between(double min, double max) {
  /* Random real in [0, 1) */
  return min + (max - min)*random_double();
}

/* Common Headers */

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif /* RTWEEKEND_H */

