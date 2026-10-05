#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"


typedef enum MaterialType_e {
  Material_Lambertian,
  Material_Metal,
} MaterialType;

typedef struct Material {
  MaterialType type;
  color albedo;
} Material;


bool scatter(Material* mat, const ray* r_in, const HitRec* rec,
             color* attenuation, ray* scattered)
{
  switch (mat->type) {
    case Material_Lambertian:
    {
      vec3 scatterDir = addVec(rec->normal, randomUnitVec());
      // Catch degenerate scatter direction
      if (near_zero(&scatterDir))
        scatterDir = rec->normal;

      *scattered = (ray){ rec->p, scatterDir };
      *attenuation = mat->albedo;
      return true;
      break;
    }
    case Material_Metal:
    {
      vec3 reflectDir = reflect(r_in->dir, rec->normal);
      *scattered = (ray){ rec->p, reflectDir };
      *attenuation = mat->albedo;
      return true;
      break;
    }
  }
}

#endif // !MATERIAL_H

