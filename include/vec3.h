#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>


typedef struct vec3_s {
  #ifndef VEC_HALF_PREC
  double x, y, z;
  #else
  float x, y, z;
  #endif
} vec3;

vec3 negVec(const vec3 v) {
  vec3 nv = {-v.x, -v.y, -v.z};
  return nv;
}

void incByVec(vec3* v, vec3* u) {
  v->x += u->x;
  v->y += u->y;
  v->z += u->z;
}

void incVecIn(vec3* v, double t) {
  v->x *= t;
  v->y *= t;
  v->z *= t;
}

/* Macro for incVecIn */
#define scaleVec(v, t) incVecIn((v), (t))

void divVecBy(vec3* v, double t) {
  incVecIn(v, 1/t);
}

double vecLenSq(const vec3 v) {
  return v.x*v.x + v.y*v.y + v.z*v.z;
}

double vecLen(const vec3 v) {
  return sqrt(vecLenSq(v));
}

/* point3 is an alias for vec3 */
typedef vec3 point3;


void incVecBy(vec3* v, double t) {
  v->x += t;
  v->y += t;
  v->z += t;
}

/* Vector Utility Functions */

/*conts char* vecStr(vec3* v) {
  return 
}*/

void printVec(const vec3* v) {
  fprintf(stderr, "%f %f %f", v->x, v->y, v->z);
}

vec3 addVec(const vec3 v, const vec3 u) {
  vec3 n = {v.x + u.x, v.y + u.z, v.z + u.z};
  return n;
}

vec3 subVec(const vec3 v, const vec3 u) {
  vec3 n = {v.x - u.x, v.y - u.z, v.z - u.z};
  return n;
}

vec3 multVec(const vec3 v, const vec3 u) {
  vec3 n = {v.x * u.x, v.y * u.z, v.z * u.z};
  return n;
}

vec3 multVecBy(const vec3 v, double t) {
  vec3 n = {v.x * t, v.y * t, v.z * t};
  return n;
}

vec3 divVec(const vec3 v, double t) {
  return multVecBy(v, 1/t);
}

double dot(const vec3 v, const vec3 u) {
  return v.x * u.x + v.y * u.y + v.z * u.z;
}

vec3 cross(const vec3 v, const vec3 u) {
  vec3 n = {
    v.y * u.z - v.z * u.y,
    v.z * u.x - v.x * u.z,
    v.x * u.y - v.y * u.x
  };
  return n;
}

vec3 unitVec(const vec3 v) {
  return divVec(v, vecLen(v));
}

#endif /* VEC3_H */

