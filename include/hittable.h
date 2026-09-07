#ifndef HITTABLE_H
#define HITTABLE_H

typedef struct hit_record_s {
  point3 p;
  vec3 normal;
  double t;
  int isFrontFace;
} HitRec;


typedef enum {
  Hittable_Circle,
} HittableType;

typedef struct {
  HittableType type;
  point3 center;
  double radius;
} Hittable;


void setFaceNormal(HitRec* rec, const ray* r, const vec3* outwardNormal) {
  /* Sets the hit record normal vector. */
  /* NOTE: the outwardNormal is assumed to have unit len. */
  rec->isFrontFace = dot(r->dir, *outwardNormal) < 0.;
  rec->normal = rec->isFrontFace ? *outwardNormal : negVec(*outwardNormal);
}

bool hit(const Hittable* hittable, const ray* r, double tmin, double tmax, HitRec* rec) {
  switch (hittable->type) {
    case Hittable_Circle: {
      point3 center = hittable->center;
      double radius = hittable->radius;

      vec3 oc = subVec(center, r->orig);
      double a = vecLenSq(r->dir);
      double h = dot(r->dir, oc);
      double c = vecLenSq(oc) - radius*radius;

      double discriminant = h*h - a*c;
      if (discriminant < 0)
        return false;

      double sqd = sqrt(discriminant);
      double root = (h - sqd) / a;
      if (root <= tmin || tmax <= root) {
        root = (h + sqd) / a;
        if (root <= tmin || tmax <= root)
          return false;
      }

      rec->t = root;
      rec->p = ray_at(*r, rec->t);
      vec3 outwardNormal = divVec(subVec(rec->p, center), radius);
      setFaceNormal(rec, r, &outwardNormal);

      return true;
    }
      break;
  }
}

#endif /* HITTABLE_H */

