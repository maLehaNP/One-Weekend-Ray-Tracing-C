#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <rtweekend.h>
#include <hittable.h>
#include <hittable_list.h>
#include <camera.h>
#include <material.h>


int main() {
  fprintf(stderr, "PID: %ld\n", (long)getpid());

  /* World */

  Material mat_ground = { Material_Lambertian, (color){ 0.8, 0.8, 0.0 } };
  Material mat_center = { Material_Lambertian, (color){ 0.1, 0.2, 0.5 } };
  Material mat_left   = { Material_Metal,      (color){ 0.8, 0.8, 0.8 }, 0.3 };
  Material mat_right  = { Material_Metal,      (color){ 0.8, 0.6, 0.2 }, 1.0 };

  int n = 4;
  Hittable objects[] = {
    { Hittable_Circle, {  0.0,    0.0, -1.2 },   0.5, &mat_center },
    { Hittable_Circle, {  0.0, -100.5, -1.0 }, 100.0, &mat_ground },
    { Hittable_Circle, { -1.0,    0.0, -1.0 },   0.5, &mat_left   },
    { Hittable_Circle, {  1.0,    0.0, -1.0 },   0.5, &mat_right  },
  };

  HittableList world = { n, objects };

  /* Camera */

  Camera cam;

  cam.aspectRatio = 16.0 / 9.0;
  cam.imageWidth  = 1280;
  cam.nsamples = 128;
  cam.maxDepth = 32;

  camera_render(&cam, &world);

  //free(world);

  return 0;
}

