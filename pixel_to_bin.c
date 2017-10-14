#include "pixel_color.h"
#include <sdtlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>

double px_into_bin (Uint32[] m[], size_t lines, size_t cols, SDL_Surface *surface)
{
  size_t size = (cols-1) + (lines-1) * cols;
  double res[];
  for (size_t n = 0; n < size; ++n)
    res[n] = 0;
  for (size_t i = 0; i < lines; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(m[j + i * cols], surface->format, &r, &g, &b);
      if (r == g && g == b && b == 255)
        res[j + i * cols] = 1;
      else if (r == g && g == b && b == 0)
        res[j + i * cols] = 0;
      else
        res[j + i * cols] = 3; //Not black nor white
    }
  }
  return res[];
}
