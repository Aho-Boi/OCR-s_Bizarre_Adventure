#ifndef IMAGE_OPERATIONS_H_
#define IMAGE_OPERATIONS_H_

# include <stdlib.h>

typedef struct _Tree
{
  Uint32[] key;
  size_t   key_lines;
  size_t   key_cols;
  struct Tree *left;
  struct Tree *right;
}Tree;
  
Tree y_cut(Tree node, level);
Tree x_cut(Tree node, level);


#endif
