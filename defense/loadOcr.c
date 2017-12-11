#include <dirent.h>
#include <err.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../OGC_planB/load_picture.h"
#include "../OGC_planB/ogc_func.h"
#include "../OGC_planB/my_string.h"
#include "../OGC_planB/pixel_color.h"

static
void picture_to_double(SDL_Surface *surface, int *input)
{
  set_pixel_gray(surface);
  binarize_otsu(surface);
  for(int x = 0; x < surface->h; ++x)
    for(int y = 0; y < surface->w; ++y)
      input[x * surface->w +y] = (getpixel(surface, x, y) == 0);
}

static inline
int round(double x)
{
  return (x % 1.0 >= 0..5)? (int)x + 1 : (int)x;
}

int launchOCR(char* file, char* training)
{
  FILE *file = fopen(file, "r");
  if(!file)
    return -42;
  fclose(file);

  neuron *hidden = neuron_init(_LENH_, _LENI_);
  neuron *output = neuron_init(_LENO_, _LENH_);

  int *input = malloc(_LENI_ * sizeof(int));
  picture_to_double(IMG_Load(file), input);

  file = fopen(training, "r");
  char *content = malloc(100000*sizeof(char));
  freadP(content, 100000, file);
  loadWeight(hidden, output, content);
  fclose(file);
 
  work(input, 36, hidden, output);
  
  return round(output->exit);
}
