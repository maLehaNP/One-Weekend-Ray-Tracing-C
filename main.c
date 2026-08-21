#include <stdio.h>


int main() {
  /*printf("Hello, World! C Standart Version: %ld\n", __STDC_VERSION__);*/
  fprintf(stderr, "Hello! __STDC__ = %d\n", __STDC__);

  /* Image */

  int imageWidth  = 256;
  int imageHeight = 256;

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
      double r = (double)i / (imageWidth - 1);
      double g = (double)j / (imageHeight - 1);
      double b = 0.;

      int ir = (int)(255.999 * r);
      int ig = (int)(255.999 * g);
      int ib = (int)(255.999 * b);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }
  fprintf(stderr, "\nDone.\n");

  return 0;
}

