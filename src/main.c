#include <stdio.h>
#include <stdlib.h>
#include <rtweekend.h>
#include <hittable.h>
#include <hittable_list.h>


color ray_color(const ray* r, const HittableList* world);


int main() {
  fprintf(stderr, "Hello! __STDC__ = %d\n", __STDC__);

  /* Image */

  double aspectRatio = 16. / 9.;
  int imageWidth = 400;
  int imageHeight = (int)(imageWidth / aspectRatio);
  /* Ensure height is at least 1 */
  imageHeight = (imageHeight < 1) ? 1 : imageHeight;

  /* Camera */

  point3 cameraCenter = { 0., 0., 0. };
  double focalLength = 1.;

  /* Virtual Viewport */
  double viewportHeight = 2.;
  double viewportWidth = viewportHeight * (double)imageWidth / imageHeight;
  fprintf(stderr, "imW=%d imH=%d vpW=%f vpH=%f\n",
          imageWidth, imageHeight, viewportWidth, viewportHeight);

  /* Vectors across horiz. & vert. viewport edges */
  vec3 vp_u = {viewportWidth, 0., 0.};
  vec3 vp_v = {0., -viewportHeight, 0.};  /* Fixed bag */

  /* Pixel to pixel delta vectors */
  vec3 pixel_delta_u = divVec(vp_u, imageWidth);
  vec3 pixel_delta_v = divVec(vp_v, imageHeight);

  /* Upper left pixel */
  vec3 vp2cam = {0, 0, focalLength};
  point3 vp_upper_left = subVec(
    subVec(
      subVec(cameraCenter, vp2cam),
      divVec(vp_u, 2.)
    ),
    divVec(vp_v, 2.)
  );
  point3 pix00 = addVec(vp_upper_left, multVecBy(addVec(pixel_delta_u, pixel_delta_v), 0.5));


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
  int i;
  for (i = 0; i < n; ++i)
    world->objects[i] = objects[i];

  /* Render */

  printf("P3\n");  /* P3 means colors are in ASCII */
  printf("%d %d\n", imageWidth, imageHeight);  /* "columns rows" */
  printf("255\n");  /* Max color */

  int j;
  for (j = 0; j < imageHeight; j++)
  {
    fprintf(stderr, "\rScanlines remaining: %d           ", imageHeight - j);
    /*fflush(stderr);*/  /* Flush to display immediately */
    int i;
    for (i = 0; i < imageWidth; i++)
    {
      point3 pixelCenter = addVec(
        pix00,
        addVec(
          multVecBy(pixel_delta_u, i),
          multVecBy(pixel_delta_v, j)
        )
      );
      vec3 rayDir = subVec(pixelCenter, cameraCenter);
      ray r = {cameraCenter, rayDir};
      color pixelColor = ray_color(&r, world);
      writeColor(stdout, &pixelColor);
    }
  }
  fprintf(stderr, "\nDone.\n");

  free(world);

  return 0;
}


color ray_color(const ray* r, const HittableList* world) {
  HitRec rec;
  interval ray_t = { 0., infinity };
  if (hit_List(world, r, ray_t, &rec)) {
    color white = { 1., 1., 1. };
    return multVecBy(addVec(rec.normal, white), 0.5);
  }

  vec3 unitDir = unitVec(r->dir);
  double a = 0.5*(unitDir.y + 1.);
  color start = {1.0, 1.0, 1.0};
  color end   = {0.5, 0.7, 1.0};
  /*color end   = {0.0, 0.0, 0.0};*/
  return addVec(multVecBy(start, (1.-a)), multVecBy(end, a));
}

