#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"


color ray_color(const ray* r, const HittableList* world);


typedef struct {
  double aspectRatio;
  int    imageWidth;
  int    imageHeight;
  point3 center;
  point3 pix00;          /* Location of pixel (0, 0) */
  vec3   pixel_delta_u;  /* Offset to pixel to the right */
  vec3   pixel_delta_v;  /* Offset to pixel below */
} Camera;

void camera_init(Camera* camera) {
  double aspectRatio = camera->aspectRatio;
  int    imageWidth  = camera->imageWidth;

  int imageHeight = (int)(imageWidth / aspectRatio);
  /* Ensure height is at least 1 */
  imageHeight = (imageHeight < 1) ? 1 : imageHeight;
  camera->imageHeight = imageHeight;

  /* Camera */

  point3 cameraCenter = { 0., 0., 0. };
  camera->center = cameraCenter;

  /* Virtual Viewport */

  double focalLength = 1.;
  double viewportHeight = 2.;
  double viewportWidth = viewportHeight * (double)imageWidth / imageHeight;
  /*
  fprintf(stderr, "imW=%d imH=%d vpW=%f vpH=%f\n",
          imageWidth, imageHeight, viewportWidth, viewportHeight);
  */

  /* Vectors across horiz. & vert. viewport edges */
  vec3 vp_u = {viewportWidth, 0., 0.};
  vec3 vp_v = {0., -viewportHeight, 0.};  /* Fixed bag */

  /* Pixel to pixel delta vectors */
  vec3 pixel_delta_u = divVec(vp_u, imageWidth);
  vec3 pixel_delta_v = divVec(vp_v, imageHeight);
  camera->pixel_delta_u = pixel_delta_u;
  camera->pixel_delta_v = pixel_delta_v;

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
  camera->pix00 = pix00;
}

void camera_render(Camera* cam, HittableList* world) {
  camera_init(cam);

  /* Render */

  printf("P3\n");  /* P3 means colors are in ASCII */
  printf("%d %d\n", cam->imageWidth, cam->imageHeight);  /* "columns rows" */
  printf("255\n");  /* Max color */

  int j;
  for (j = 0; j < cam->imageHeight; j++)
  {
    fprintf(stderr, "\rScanlines remaining: %d           ", cam->imageHeight - j);
    /*fflush(stderr);*/  /* Flush to display immediately */
    int i;
    for (i = 0; i < cam->imageWidth; i++)
    {
      point3 pixelCenter = addVec(
        cam->pix00,
        addVec(
          multVecBy(cam->pixel_delta_u, i),
          multVecBy(cam->pixel_delta_v, j)
        )
      );
      vec3 rayDir = subVec(pixelCenter, cam->center);
      ray r = {cam->center, rayDir};
      color pixelColor = ray_color(&r, world);
      writeColor(stdout, &pixelColor);
    }
  }
  fprintf(stderr, "\nDone.\n");
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

#endif /* CAMERA_H */

