#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <rtweekend.h>
#include <hittable.h>
#include <hittable_list.h>
#include <camera.h>


int main() {
  fprintf(stderr, "PID: %ld\n", (long)getpid());

  /* World */

  int n = 2;
  Hittable objects[] = {
    { Hittable_Circle, { 0,      0, -1 },   0.5 },
    { Hittable_Circle, { 0, -100.5, -1 }, 100.0 }
  };
  HittableList* world = malloc(sizeof(int) + n * sizeof(Hittable));
  if (!world)
    return 1;
  world->n = n;
  for (int i = 0; i < n; ++i)
    world->objects[i] = objects[i];

  /* Camera */

  Camera cam;

  cam.aspectRatio = 16.0 / 9.0;
  cam.imageWidth  = 1280;
  cam.nsamples = 64;
  cam.maxDepth = 32;

  camera_render(&cam, world);

  free(world);

  return 0;
}

