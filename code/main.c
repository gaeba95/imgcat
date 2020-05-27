#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "environment.h"
#include "convert.h"
#include "imgcat.h"

int main(int argc, char **argv) {
  int i, print_width = 0, image_type = IMAGE_TYPE_INVALID;
  char *filename = 0;
  FILE *imgfile;
  raster_t *raster;

  for (i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-w") == 0) {
      if (i+1 < argc) {
	print_width = atoi(argv[i+1]);
	if (print_width < 1) {
	  fprintf(stderr, "Usage: -w NUMCHARSWIDE\n");
	  exit(1);
	}
	++i;
      } else {
	fprintf(stderr, "Usage: -w NUMCHARSWIDE\n");
	exit(1);
      }
    } else {
      filename = argv[i];
      image_type = get_image_type(filename);
    }
  }

  if (print_width < 1) {
    print_width = get_terminal_width();
  }

  if (filename) {
    imgfile = fopen(filename, "rb");
    if (!imgfile) {
      fprintf(stderr, "Failed to open image file %s.\n", filename);
      exit(1);
    }
  } else {
    image_type = IMAGE_TYPE_BITMAP;
    imgfile = stdin;
  }

  switch (image_type) {
    case IMAGE_TYPE_BITMAP:
      raster = create_raster_from_bmp(imgfile);
      break;
    case IMAGE_TYPE_JPEG:
      raster = create_raster_from_jpg(imgfile);
      break;
    case IMAGE_TYPE_PNG:
      raster = create_raster_from_png(imgfile);
      break;
    case IMAGE_TYPE_INVALID:
    default:
      fprintf(stderr, "Unable to detect valid image format.\n");
      exit(5);
  }

  fclose(imgfile);

  if (!raster) {
    fprintf(stderr, "Failed to get pixel data from file.\n");
    exit(1);
  }

  print_raster(raster, print_width);

  free_raster(raster);
  return 0;
}