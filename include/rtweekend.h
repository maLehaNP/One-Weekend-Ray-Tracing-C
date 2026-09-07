#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>

/* Common Headers */

#include "color.h"
#include "ray.h"
#include "vec3.h"

/* Constants */

const double infinity = DBL_MAX;
const double pi = 3.1415926535897932385;

/* Utility Functions */

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#endif /* RTWEEKEND_H */

