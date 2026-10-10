#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"


typedef enum MaterialType_e {
  Material_Lambertian,
  Material_Metal,
  Material_Dielectric,
} MaterialType;

typedef struct Material {
  MaterialType type;
  color albedo;
  double fuzz;
  double refractionIndex;
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
      reflectDir = addVec(unitVec(reflectDir), multVecBy(randomUnitVec(), mat->fuzz));
      *scattered = (ray){ rec->p, reflectDir };
      *attenuation = mat->albedo;
      return (dot(scattered->dir, rec->normal) > 0.);
      break;
    }
    case Material_Dielectric:
    {
      *attenuation = (color){ 1.0, 1.0, 1.0 };  // glass surface absorbs nothing
      double ri = rec->isFrontFace ? (1.0/mat->refractionIndex) : mat->refractionIndex;

      vec3 unitDir = unitVec(r_in->dir);
      //vec3 refracted = refract(&unitDir, &rec->normal, ri);
      double cos_theta = fmin(dot(negVec(unitDir), rec->normal), 1.0);
      double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

      bool cannot_refract = (ri * sin_theta) > 1.0;
      vec3 dir;

      if (cannot_refract)
        dir = reflect(unitDir, rec->normal);
      else
        dir = refract(&unitDir, &rec->normal, ri);

      //*scattered = (ray){ rec->p, refracted };
      *scattered = (ray){ rec->p, dir };

      return true;
      break;
    }
    default:
      return false;
      break;
  }
}

#endif // !MATERIAL_H

