#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

typedef vec3 color;

void writeColor(FILE* fptr, const color pixelColor) {
  double r = pixelColor.x;
  double g = pixelColor.y;
  double b = pixelColor.z;

  /* [0, 1] -> [0, 255] */
  static const interval intensity = { 0.000, 0.999 };
  int rbyte = (int)(255.999 * interval_clamp(&intensity, r));
  int gbyte = (int)(255.999 * interval_clamp(&intensity, g));
  int bbyte = (int)(255.999 * interval_clamp(&intensity, b));

  fprintf(fptr, "%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif /* COLOR_H */

