# include "image_operations.h"
# include "load_picture.h"
# include <sdtlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

Tree surface_to_tree(SDL_Surface *surface)
{
  Uint32 pixel_matrix[surface->h * surface->w];
  for(int x = 0; x < surface->h; x++)
  {
    for(int y = 0; y < surface->w; Y++)
    {
      pixel_matrix[x * surface->w + y] = getpixel(surface, x, y);
    }
  }
  Tree node;
  node->key = pixel_matrix;
  node->key_lines = surface->h;
  node->key_cols = surface->w;
  return node;
}

Tree  y_cut(Tree node, int level)
{
  if(level == 4)
    return;
  else
  {
    int c = 0;
    size_t lines = node->key_lines;
    size_t cols = node->key_cols;
    Uint32 pixel_matrix[lines * cols] = node->key;
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
     {
       c = 1;
       break;
     }
    }
    if(c == 1)
    {
      Tree nodel;
      Tree noder;
      Uint32 upper[lines * y];
      Uint32 down[lines * (cols - y)];
      for(size_t j = 0; j < y; j++)
      {
        for(size_t i = 0; i < lines; i++)
        {
          upper[i * y + j] = pixel_matrix[i * y + j];
        }
      }
      for(size_t j = 0; j < (cols - y); j++)
      {
        for(size_t i = 0; i < lines; i++)
        {
          down[i * (cols - y)  + j] = pixel_matrix[i * (cols - y) + j];
        }
      }
      nodel->key = upper;
      nodel->key_lines = lines;
      nodel->key_cols = y;
      node->left = nodel;
      noder->key = down;
      noder->key_lines = lines;
      noder->key_cols = cols - y;
      node->right = noder;
      x_cut(node->left, 1);
      y_cut(node->right, 1);
    }
    return x_cut(node, level + 1);
  }
}

Tree x_cut(Tree node, int level)
{
  if(level == 4)
    return;
  else
  {
    int c = 0;
    size_t lines = node->key_lines;
    size_t cols = node->key_cols;
    Uint32 pixel_matrix[lines * cols] = node->key;
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
      {
        c = 1;
        break;
      }
    }
    if(c == 1)
    {
      Tree nodel;
      Tree noder;
      Uint32 left[x * cols];
      Uint32 right[(lines - x) * cols];
      for(size_t i = 0; i < x; i++)
      {
        for(size_t j = 0; j < cols; j++)
        {
          left[ i * cols + j] = pixel_matrix[i * cols + j];
        }
      }
      for(size_t i = 0; i < (lines - x); i++)
      { 
        for(size_t j = 0; j < cols; j++)
        {
          right[i * (lines - x)  + j] = pixel_matrix[i * (lines - x) + j];
        }
      }
      nodel->key = left;
      nodel->key_lines = x;
      nodel->key_cols = cols;
      node->left = nodel;
      noder->key = right;
      noder->key_lines = lines - x;
      noder->cols = cols;
      node->right = noder;
      y_cut(node->left, 1);
      x_cut(node->right, 1);
    }
    return y_cut(pixel_matrix, lines, cols, level + 1);
  }
}

