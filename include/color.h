#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

void writeColor(FILE* fptr, const color* pixelColor) {
  double r = pixelColor->x;
  double g = pixelColor->y;
  double b = pixelColor->z;

  /* [0, 1] -> [0, 255] */
  int rbyte = (int)(255.999 * r);
  int gbyte = (int)(255.999 * g);
  int bbyte = (int)(255.999 * b);

  fprintf(fptr, "%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif /* COLOR_H */

