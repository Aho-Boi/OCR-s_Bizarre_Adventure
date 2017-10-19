# include "image_operations.h"
# include "load_picture.h"
# include <sdtlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>


void  y_cut(SDl_Surface *surface, int level)
{
  if(level == 4)
    return;
  else
  {
    int c = 0;
    SDL_Surface pic = node->key;
    int white_lines = 0 ;
    int count_pixel = 0;
    int mid = pic->h/ 4
    for(int y = 0; y < pic->h; y++)
    {  
     for(int x = 0 ; x < pic->w; x++)
     {
       if(getpixel(surface, x, y) != 0)
          count_pixel += 1;
     }
     if(count_pixel = pic->h - 1)
        white_lines += 1;
     else
       count_pixel = 0;
     if(white_lines >= mid)
     {
       c = 1;
       break;
     }
    }
    if(c == 1)
    {
      Tree nodel;
      Tree noder;
      SDL_Surface upper = SDL_CreateRGBSurface(0, pic->w, y, );
      SDL_Surface down = SDL_CreateRGBSurface(0, pic->w, y,);
      nodel->key = upper;
      nodel->key = down;
      node->left = nodel;
      node->right = noder;
      x_cut(node->right, 1);
      y_cut(node->left, 1);
    }
    return x_cut(surface, level + 1);
  }
}

void  x_cut(SDl_Surface *surface, int level)
{
  if(level != 4)
  {
    int c = 0;
    SDL_Surface  pic = node->key;
    int white_space = 0 ;
    int count_pixel = 0;
    int mid = pic->w/8;
    for(size_t x = 0; x < pic->w; x++)
    { 
      for(size_t y = 0 ; y < pic->h; y++)
      {
        if(getpixel(surface, x, y) != 0)
          count_pixel += 1;
      }
      if(count_pixel = pic->w - 1)
        white_space += 1;
      else
        count_pixel = 0;
      if(white_space >= mid)
      {
        c = 1;
        break;
      }
    }
    if(c == 1)
    {
      Tree nodel;
      Tree noder;
      SDL_Surface left = SDL_CreateRGBSurface(0, x, pic->h,);
      SDL_Surface right = SDL_CreateRGBSurface(0,x, pic->h, ):
      nodel->key = left;
      noder->key = right;
      node->left = nodel
      node->right = noder;
      y_cut(node->right, 1);
      x_cut(node->left, 1);
    }
    return y_cu(node, level + 1);
  }
}


