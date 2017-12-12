/* segmentation.h : segmentation header */

# ifndef SEGMENTATION_H
# define SEGMENTATION_H

# include <stdlib.h>

int* upp(int *mat, int line, int cols);

void upp2(int *mat, int line, int cols, int* res);

void print_mat(int *mat, int line, int col);

int* resizePixels(int *pixels, int w1, int h1, int w2, int h2);
# endif 
