#ifndef IMAGE_OPERATIONS_H_
#define IMAGE_OPERATIONS_H_

# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL_image.h>
# include "load_picture.h"


typedef struct Tree
{
  size_t   key_lines;
  size_t   key_cols;
  Uint32   *key;
  struct Tree *left;
  struct Tree *right;
}Tree;

Tree surface_to_tree(SDL_Surface *surface);
Tree y_cut(Tree node, int level);
Tree x_cut(Tree node, int level);
void display_cut(Tree node);

#endif
