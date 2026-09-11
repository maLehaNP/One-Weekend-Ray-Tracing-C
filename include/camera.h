#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "rtweekend.h"


typedef struct {
  /* Configurable */
  double aspectRatio;
  int    imageWidth;
  int    nsamples;
  int    maxDepth;

  int    imageHeight;
  point3 center;
  point3 pix00;          /* Location of pixel (0, 0) */
  vec3   pixel_delta_u;  /* Offset to pixel to the right */
  vec3   pixel_delta_v;  /* Offset to pixel below */
  double pixel_samples_scale;
} Camera;

void camera_init(Camera* camera) {
  double aspectRatio = camera->aspectRatio;
  int    imageWidth  = camera->imageWidth;

  int imageHeight = (int)(imageWidth / aspectRatio);
  /* Ensure height is at least 1 */
  imageHeight = (imageHeight < 1) ? 1 : imageHeight;
  camera->imageHeight = imageHeight;

  camera->pixel_samples_scale = 1. / camera->nsamples;

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

vec3 sample_square() {
  /* Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square. */
  vec3 v = { random_double() - 0.5, random_double() + 0.5, 0. };
  return v;
}

ray get_ray(int i, int j, Camera* cam) {
  vec3 offset = sample_square();

  point3 pixelSample = addVec(
    cam->pix00,
    addVec(
      multVecBy(cam->pixel_delta_u, i + offset.x),
      multVecBy(cam->pixel_delta_v, j + offset.y)
    )
  );

  vec3 rayDir = subVec(pixelSample, cam->center);
  ray r = { cam->center, rayDir };

  return r;
}

color ray_color(const ray* r, const HittableList* world, int depth) {
  /* Bounce limit */
  if (depth <= 0) {
    color black = { 0., 0., 0. };
    return black;
  }

  HitRec rec;
  interval ray_t = { 0.001, infinity };

  if (hit_List(world, r, ray_t, &rec)) {
    /*color white = { 1., 1., 1. };
    return multVecBy(addVec(rec.normal, white), 0.5);*/
    vec3 bounceDir = randomOnHem(&rec.normal);
    ray bouncedRay = { rec.p, bounceDir };
    return multVecBy(ray_color(&bouncedRay, world, depth - 1), 0.5);
  }

  vec3 unitDir = unitVec(r->dir);
  double a = 0.5*(unitDir.y + 1.);
  color start = {1.0, 1.0, 1.0};
  color end   = {0.5, 0.7, 1.0};
  /*color end   = {0.0, 0.0, 0.0};*/
  return addVec(multVecBy(start, (1.-a)), multVecBy(end, a));
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
      color pixelColor = { 0., 0., 0. };
      int s;
      for (s = 0; s < cam->nsamples; ++s) {
        ray r = get_ray(i, j, cam);
        color rc = ray_color(&r, world, cam->maxDepth);
        incByVec(&pixelColor, &rc);
      }
      writeColor(stdout, multVecBy(pixelColor, cam->pixel_samples_scale));
    }
  }
  fprintf(stderr, "\nDone.\n");
}

#endif /* CAMERA_H */

