# include "pixel_color.h"
# include <sdtlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

Uint32[] surface_to_matrix(SDL_Surface *surface)
{
  Uint32 pixel_matrix[surface->h * surface->w];
  for(int x = 0; x < surface->h; x++)
  {
    for(int y = 0; y < surface->w; Y++)
    {
      pixel_matrix[x * surface->w + y] = getpixel(surface, x, y);
    }
  }
  return pixel_matrix;
}

size_t y_cut(Uint32[] pixel_matrix, size_t lines, size_t cols)
{
  size_t cut = 0;
  int white_lines = 0 ;
  int count_pixel = 0;
  size_t mid = lines/ 4
  for(size_t y = 0; y < cols; y++)
  { 
    for(size_t x = 0 ; x < lines; x++)
    {
      if(pixel_matrix[x * cols + y] != 0)
         count_pixel += 1;
    }
    if(count_pixel = lines - 1)
       white_lines += 1;
       cut = y;
    else
      count_pixel = 0;
    if(white_lines >= mid)
      break;
  }
  return cut;
}

size_t x_cut(Uint32[] pixel_matrix, size_t lines, size_t cols)
{
  size_t cut = 0;
  int white_space = 0 ;
  int count_pixel = 0;
  size_t mid = cols/8;
  for(size_t x = 0; x < lines; x++)
  { 
    for(size_t y = 0 ; y < cols; y++)
    {
      if(pixel_matrix[x * cols + y] != 0)
         count_pixel += 1;
    }
    if(count_pixel = lines - 1)
       white_space += 1;
       cut = x;
    else
      count_pixel = 0;
    if(white_space >= mid)
      break;
  }
  return cut;

}

