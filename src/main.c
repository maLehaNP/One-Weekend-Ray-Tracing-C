#include <stdio.h>
#include <vec3.h>
#include <color.h>
#include <ray.h>


color ray_color(const ray* r) {
  color c = {0, 0, 0};
  return c;
}


int main() {
  fprintf(stderr, "Hello! __STDC__ = %d\n", __STDC__);

  /* Image */

  /*int imageWidth  = 256;*/
  /*int imageHeight = 256;*/
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
  vec3 vp_v = {0. -viewportHeight, 0.};

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
      point3 pixelCenter = addVec(addVec(pix00, multVecBy(pixel_delta_u, i)), multVecBy(pixel_delta_v, j));
      vec3 rayDir = subVec(pixelCenter, cameraCenter);
      ray r = {cameraCenter, rayDir};
      /*color pixelColor = {
        (double)i / (imageWidth - 1),
        (double)j / (imageHeight - 1),
        0.
      };*/
      color pixelColor = ray_color(&r);
      writeColor(stdout, &pixelColor);
    }
  }
  fprintf(stderr, "\nDone.\n");

  return 0;
}

