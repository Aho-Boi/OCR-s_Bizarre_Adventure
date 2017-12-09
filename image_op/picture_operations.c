
# include "picture_operations.h"
# include "load_picture.h"
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL_image.h>
# define couleur(param) printf("\033[%sm",param)

Tree surface_to_tree(SDL_Surface *surface)
{
  double pixel_matrix[surface->h * surface->w];
  for(int x = 0; x < surface->w; x++)
  {
    for(int y = 0; y < surface->h; y++)
    {   
      if(getpixel(surface, x, y) != 0)
      {
        pixel_matrix[y * surface->w + x] = 1;
      }
      else
      {
        pixel_matrix[y * surface->w + x] = 0;
      }
    }
  }
  Tree node;
  node.valid = 1;
  node.key = pixel_matrix;
  node.key_lines = surface->h;
  node.key_cols = surface->w;
  return node;
}

void addNode(Tree **tree, double key[], size_t lines, size_t cols, int lor)
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

size_t can_cut_y(double pixel_matrix[], size_t lines, size_t cols)
{
  size_t cut = 0;
  size_t lim_count = lines * cols;
  size_t count = 0;
  size_t mid = lines/(lines * cols);
  for(size_t y = 0; y < cols; y++)
  {
    size_t i = y;
    while(i < lim_count && pixel_matrix[i] == 1)
    {
      i += cols;
    }
    if(i < lim_count)
    {
      count += 1;
    }
    else
    {
      count = 0;
    }
    if(count >= mid)
    {
      cut = y;
      break;
    }
  }
  return cut;
}

Tree y_cut(Tree *node, int level)
{
  if(level == 3)
  {
    return *node;
  }
  else
  {
    size_t lines = node->key_lines;
    size_t cols = node->key_cols;
    size_t c;
    c = can_cut_y(node->key, lines, cols);
    if(c != 0)
    {
      double upper[lines * c];
      double down[lines * (cols - c)];
      for(size_t j = 0; j < c; j++)
      {
        for(size_t i = 0; i < lines; i++)
        {
          double value = node->key[i * cols + j];
          upper[i * cols + j] = value;
        }
      }
      for(size_t j = (cols - c); j < cols; j++)
      {
        for(size_t i = 0; i < lines; i++)
        {
          double value = node->key[i * cols + j];
          down[i * cols + j] = value;
        }
      }
        addNode(&node, upper, lines, c, 0);
        addNode(&node, down, lines, cols - c, 1);
        x_cut(node->left, 1);
        y_cut(node->right, 1);
      return *node;
    }
    else
      return x_cut(node, level + 1);
  }
}

size_t can_cut_x(double pixel_matrix[], size_t lines, size_t cols)
{
  size_t cut = 0;
  size_t lim_count = lines * cols;
  size_t count = 0;
  size_t mid = lines/(lines * cols);
  for(size_t x = 0; x < lines; x++)
  {
    size_t i = x;
    while(i < lim_count && pixel_matrix[i] == 1)
    {
      i += lines;
    }
    if(i < lim_count)
    {
      count += 1;
    }
    else
    {
      count = 0;
    }
    if(count >= mid)
    {
      cut = x;
      break;
    }
  }
  return cut;

}

Tree x_cut(Tree *node, int level)
{
  if(level == 3)
  {
    return *node;
  }
  else
  {
    size_t c;
    size_t lines = node->key_lines;
    size_t cols = node->key_cols;
    c = can_cut_x(node->key, lines, cols);
    if(c != 0)
    {
      double left[c * cols];
      double right[(lines - c) * cols];
      for(size_t i = 0; i < c; i++)
      {
        for(size_t j = 0; j < cols; j++)
        {
          double value = node->key[i * cols + j];
          left[i *  cols + j] = value;
        }
      }
      for(size_t i = (lines - c); i < lines; i++)
      {
        for(size_t j = 0; j < cols; j++)
        {
          double value = node->key[i * cols + j];
          right[i * cols + j] = value;
        }
      }
      addNode(&node, left, c, cols, 0);
      addNode(&node, right, lines - c, cols, 1);
      y_cut(node->left, 1);
      x_cut(node->right, 1);
      return *node;
    }
    else
      return y_cut(node, level + 1);
  }
}

void resize(double mat[], size_t lines, size_t cols, double res[])
{
  if(lines < 16 && cols < 16)
  {
    for(size_t i = 0; i < lines; i++)
    {
      for(size_t j = 0; j < cols; j++)
      {
        res[i] = mat[i];
      }
    }
    for(int i = lines; i < 16; i++)
    {
      for(size_t j = cols; j < 16; j++)
      {
        res[i] = 1;
      }
    }
  }
  else
  {
    if(lines > 16 || cols > 16)
    {
      size_t i1 = 0;
      if(lines > 16)
      {
        size_t j1 = 0;
        while(i1 < 4 && j1 < cols && mat[i1] == 1)
        {
          if(mat[i1] == 1)
          {
            i1++;
            /*
            j1++;
            if(j1 >= cols)
            {
              j1 = 0;
              i1++;
            }*/
          }
        }
      }
      size_t j2 = 0;
      if(cols > 16)
      {
        size_t i2 = 0;
        while(i2 < lines && j2 < 4 && mat[j2] == 1)
        {
          j2++;
          /*
          if(mat[i2 * cols + j2] == 1)
          {
            i2++;
            if(i2 >= lines)
            {
              i2 = 0;
              j1++;
            }
          }
          */
        }
      }
      for(size_t x = 0; x < 16; x++)
      {
        for(size_t y = 0; j2 < 16 ; y++)
        {
          res[x] = mat[x + i1 + j2];
        }
      }
    }      
  }
}

void print_matrix(double mat[], size_t lines, size_t cols)
{
  for(size_t i = 0; i < lines; i++)
  {
    for(size_t j = 0; j < cols; j++)
    {
      if(mat[i * cols + j] == 0)
      {
        couleur("31");
        printf("%f ", mat[i * cols + j]);
        couleur("0");
      }
      else
        printf("%f ", mat[i * cols + j]);
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
    /*double res[16 * 16];
      resize(node->key, line, cols, res); */
      print_matrix(node->key, node->key_lines, node->key_cols);
    }
    if(node->left)
      display_cut(node->left);
    if(node->right)
      display_cut(node->right);
  } 
}

