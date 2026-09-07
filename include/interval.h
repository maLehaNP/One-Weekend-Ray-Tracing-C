#ifndef INTERVAL_H
#define INTERVAL_H

typedef struct {
  double min, max;
} interval;

/*interval interval() {
  interval i = { +infinity, -infinity };
}*/

double interval_size(interval* i) {
  return i->max - i->min;
}

bool interval_contains(interval* i, double x) {
  return i->min <= x && x <= i->max;
}

bool interval_surrounds(interval* i, double x) {
  return i->min < x && x < i->max;
}

double interval_clamp(const interval* i, double x) {
  if (x < i->min) return i->min;
  if (x > i->max) return i->max;
  return x;
}

const interval empty    = { +infinity, -infinity };
const interval universe = { -infinity, +infinity };

#endif /* INTERVAL_H */

