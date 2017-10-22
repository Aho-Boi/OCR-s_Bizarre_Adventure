# include "picture_operations.h"
# include "load_picture.h"
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL_image.h>


Tree surface_to_tree(SDL_Surface *surface)
{
  Uint32 pixel_matrix[surface->h * surface->w];
  for(int x = 0; x < surface->h; x++)
  {
    for(int y = 0; y < surface->w; y++)
    {
      Uint32 value = getpixel(surface, x, y);
      pixel_matrix[x * surface->w + y] = value;
    }
  }
  Tree node;
  node.valid = 1;
  node.key = pixel_matrix;
  node.key_lines = surface->h;
  node.key_cols = surface->w;
  return node;
}

void addNode(Tree **tree, Uint32 key[], size_t lines, size_t cols, int lor)
{
    Tree *tmpNode;
    Tree *tmpTree = *tree;
    Tree *node = malloc(sizeof(node));
    node->valid = 1;
    node->key = key;
    node->key_lines = lines;
    node->key_cols = cols;
    node->left = NULL;
    node->right = NULL;

    if(tmpTree)
    {
      while(tmpTree)
      {
         if(lor == 1)
         {
          tmpNode->right = node;
         }
        if(lor == 0)
        {
          tmpNode->left = node;
        }
      }
    }
    else
    {
     *tree = node;
    }
}

Tree y_cut(Tree *node, int level)
{
  if(level == 3)
  {
    return *node;
  }
  else
  {
    int c = 0;
    size_t cut;
    size_t lines = node->key_lines;
    size_t cols = node->key_cols;
    Uint32 pixel_matrix[lines * cols];
    for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
      {
        Uint32 value = node->key[i * cols + j];
        pixel_matrix[i * cols + j] = value;
      }
    }
    int white_lines = 0 ;
    size_t count_pixel = 0;
    int mid = lines/8;
    for(size_t y = 0; y < cols; y++)
    {
     for(size_t x = 0 ; x < lines; x++)
     {
       if(pixel_matrix[x * cols + y] != 0)
       {
          count_pixel += 1;
       }
     }
     if(count_pixel == (lines - 1))
      {
        white_lines += 1;
      }
     else
     {
       count_pixel = 0;
     }
     if(white_lines >= mid)
     {
       c = 1;
       cut = y;
       break;
     }
    }
    if(c == 1)
    {
      Uint32 upper[lines * cut];
      Uint32 down[lines * (cols - cut)];
      for(size_t j = 0; j < cut; j++)
      {
        for(size_t i = 0; i < lines; i++)
        {
          Uint32 value = pixel_matrix[i * cut + j];
          upper[i * cut + j] = value;
        }
      }
      for(size_t j = (cols - cut); j < cols; j++)
      {
        for(size_t i = 0; i < lines; i++)
        {
          Uint32 value = pixel_matrix[i * (cols - cut) + j];
          down[i * (cols - cut)  + j] = value;
        }
      }
      addNode(&node, upper, lines, cut, 0);
      addNode(&node, down, lines, cols - cut, 1);
      x_cut(node->left, 1);
      y_cut(node->right, 1);
    }
    return x_cut(node, level + 1);
  }
}

Tree x_cut(Tree *node, int level)
{
  if(level == 3)
  {
    return *node;
  }
  else
  {
    int c = 0;
    size_t cut;
    size_t lines = node->key_lines;
    size_t cols = node->key_cols;
    Uint32 pixel_matrix[lines * cols];
    for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
      {
        Uint32 value = node->key[i * cols + j];
        pixel_matrix[i * cols + j] = value;
      }
    }
    int white_space = 0 ;
    size_t count_pixel = 0;
    int mid = cols/8;
    for(size_t x = 0; x < lines; x++)
    {
      for(size_t y = 0 ; y < cols; y++)
      {
        if(pixel_matrix[x * cols + y] != 0)
        {
          count_pixel += 1;
        }
      }
      if(count_pixel == (lines - 1))
      {
        white_space += 1;
      }
      else
      {
        count_pixel = 0;
      }
      if(white_space >= mid)
      {
        c = 1;
        cut = x;
        break;
      }
    }
    if(c == 1)
    {
      Uint32 left[cut * cols];
      Uint32 right[(lines - cut) * cols];
      for(size_t i = 0; i < cut; i++)
      {
        for(size_t j = 0; j < cols; j++)
        {
          Uint32 value = pixel_matrix[i * cols + j];
          left[ i * cols + j] = value;
        }
      }
      for(size_t i = (lines - cut); i < lines; i++)
      {
        for(size_t j = 0; j < cols; j++)
        {
          Uint32 value = pixel_matrix[i * cols + j];
          right[i * cols  + j] = value;
        }
      }
      addNode(&node, left, cut, cols, 0);
      addNode(&node, right, lines - cut, cols, 1);
      y_cut(node->left, 1);
      x_cut(node->right, 1);
    }
    return y_cut(node, level + 1);
  }
}

void print_matrix(Uint32 mat[], size_t lines, size_t cols)
{
 for(size_t i = 0; i < lines; i++)
 {
  for(size_t j = 0; j < cols; j++)
  {
   printf("%4d", mat[j + i * cols]);
  }
  printf("\n");
 }
}

void display_cut(Tree *node)
{
  if(node->valid)
  {
    if(!node->left && !node->right)
    {
      size_t line = node->key_lines;
      size_t cols = node->key_cols;
      print_matrix(node->key, line, cols);
    }
    if(node->left)
      display_cut(node->left);
    if(node->right)
      display_cut(node->right);
  }
}
