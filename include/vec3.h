#ifndef VEC3_H
#define VEC3_H

//#include <x86intrin.h>  // Include all of the intrinsics headers


typedef struct vec3_s {
  #ifndef VEC_HALF_PREC
  double x, y, z;
  #else
  float x, y, z;
  #endif
} vec3;

//typedef union vec3_s {
//  #ifndef VEC_HALF_PREC
//  struct {
//    double x, y, z;
//  }
//  double e[3];
//  #else
//  float x, y, z;
//  #endif
//} vec3;


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
  incVecIn(v, 1./t);
}

double vecLenSq(const vec3 v) {
  return v.x*v.x + v.y*v.y + v.z*v.z;
}

bool near_zero(vec3* v) {
  // Return true if the vector is close to zero in all dimensions.
  double s = 1e-8;
  return (fabs(v->x) < s) && (fabs(v->y) < s) && (fabs(v->z) < s);
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

inline void printVec(const vec3* v) {
  fprintf(stderr, "%f %f %f", v->x, v->y, v->z);
}

inline vec3 addVec(const vec3 v, const vec3 u) {
  vec3 n = {v.x + u.x, v.y + u.y, v.z + u.z};
  return n;
}

inline vec3 subVec(const vec3 v, const vec3 u) {
  vec3 n = {v.x - u.x, v.y - u.y, v.z - u.z};
  return n;
}

inline vec3 multVec(const vec3 v, const vec3 u) {
  vec3 n = {v.x * u.x, v.y * u.y, v.z * u.z};
  return n;
}

inline vec3 multVecBy(const vec3 v, double t) {
  //vec3 n = {v.x * t, v.y * t, v.z * t};
  //return n;

  return (vec3){ v.x * t, v.y * t, v.z * t };

  //__m128 r1 = _mm_set_ps(v.x, v.y, v.z, 0.0f);
  //__m128 r2 = _mm_set1_ps(t);
  //__m128 mul = _mm_mul_ps(r1, r2);
  //float res[4];
  //_mm_storeu_ps(res, mul);
  //return (vec3){ res[0], res[1], res[2] };
}

inline vec3 divVec(const vec3 v, double t) {
  return multVecBy(v, 1./t);
}

vec3 addToVec(const vec3 v, double t) {
  vec3 n = {v.x + t, v.y + t, v.z + t};
  return n;
}

inline double dot(const vec3 v, const vec3 u) {
  return v.x * u.x + v.y * u.y + v.z * u.z;
}

inline vec3 cross(const vec3 v, const vec3 u) {
  vec3 n = {
    v.y * u.z - v.z * u.y,
    v.z * u.x - v.x * u.z,
    v.x * u.y - v.y * u.x
  };
  return n;
}

inline vec3 unitVec(const vec3 v) {
  return divVec(v, vecLen(v));
}

vec3 random() {
  vec3 v = { random_double(), random_double(), random_double() };
  return v;
}

vec3 random_ranged(double min, double max) {
  vec3 v = { random_double_between(min, max), random_double_between(min, max), random_double_between(min, max) };
  return v;
}

inline vec3 randomUnitVec() {
  while (true) {
    point3 p = random_ranged(-1., 1.);
    double lensq = vecLenSq(p);
    if (1e-160 < lensq && lensq <= 1)
      return divVec(p, sqrt(lensq));
  }
}

inline vec3 randomOnHem(const vec3* normal) {
  vec3 unit = randomUnitVec();
  if (dot(unit, *normal) > 0.)
    return unit;
  else
    return negVec(unit);
}

inline vec3 reflect(const vec3 v, const vec3 n) {
  return subVec(v, multVecBy(n, 2*dot(v, n)));
}

#endif /* VEC3_H */

