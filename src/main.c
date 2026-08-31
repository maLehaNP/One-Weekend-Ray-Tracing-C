#include <stdio.h>
#include <vec3.h>
#include <color.h>
#include <ray.h>


int hit_sphere(const point3* center, double radius, const ray* r) {
  vec3 oc = subVec(*center, r->orig);
  double a = dot(r->dir, r->dir);
  double b = -2. * dot(r->dir, oc);
  double c = dot(oc, oc) - radius*radius;
  double discriminant = b*b - 4*a*c;
  return (discriminant >= 0);
}

color ray_color(const ray* r) {
  point3 sphereCentre = {0, 0, -1};
  /* If ray intersect sphere */
  if (hit_sphere(&sphereCentre, 0.5, r)) {
    color red = {1., 0., 0.};
    return red;
  }
  /*fprintf(stderr, "hit: %d\n", hit_sphere(&sphereCentre, 0.5, r));*/

  vec3 unitDir = unitVec(r->dir);
  double a = 0.5*(unitDir.y + 1.);
  color start = {1.0, 1.0, 1.0};
  color end   = {0.5, 0.7, 1.0};
  /*color end   = {0.0, 0.0, 0.0};*/
  return addVec(multVecBy(start, (1.-a)), multVecBy(end, a));
}


int main() {
  fprintf(stderr, "Hello! __STDC__ = %d\n", __STDC__);

  /* Image */

  double aspectRatio = 16. / 9.;
  int imageWidth = 400;
  int imageHeight = (int)(imageWidth / aspectRatio);
  /* Ensure height is at least 1 */
  imageHeight = (imageHeight < 1) ? 1 : imageHeight;

  /* Camera */

  point3 cameraCenter = {0., 0., 0.};
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
  fprintf(stderr, "vp_u=(%f %f %f) vp_v=(%f %f %f) pix_du=(%f %f %f) pix_dv=(%f %f %f)\n",
          vp_u.x, vp_u.y, vp_u.z, vp_v.x, vp_v.y, vp_v.z,
          pixel_delta_u.x, pixel_delta_u.y, pixel_delta_u.z,
          pixel_delta_v.x, pixel_delta_v.y, pixel_delta_v.z);

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
  fprintf(stderr, "vp_ul=(%f, %f, %f)\n",
          vp_upper_left.x, vp_upper_left.y, vp_upper_left.z);

  /* Render */

  printf("P3\n");  /* P3 means colors are in ASCII */
  printf("%d %d\n", imageWidth, imageHeight);  /* "columns rows" */
  printf("255\n");  /* Max color */

  int j;
  for (j = 0; j < imageHeight; j++)
  {
    /*fprintf(stderr, "\rScanlines remaining: %d           ", imageHeight - j);*/
    /*fflush(stderr);*/  /* Flush to display immediately */
    int i;
    for (i = 0; i < imageWidth; i++)
    {
      point3 pixelCenter = addVec(
        addVec(
          pix00,
          multVecBy(pixel_delta_u, i)
        ),
        multVecBy(pixel_delta_v, j)
      );
      /*point3 pixelCenter = addVec(pix00, multVecBy(pixel_delta_u, i));*/
      /*fprintf(stderr, "pixelCenter: %f %f %f\n", pixelCenter.x, pixelCenter.y, pixelCenter.z);*/
      vec3 rayDir = subVec(pixelCenter, cameraCenter);
      ray r = {cameraCenter, rayDir};
      /*fprintf(stderr, "r.dir: %f %f %f\n", r.dir.x, r.dir.y, r.dir.z);*/
      color pixelColor = ray_color(&r);
      writeColor(stdout, &pixelColor);
    }
  }
  fprintf(stderr, "\nDone.\n");

  return 0;
}

