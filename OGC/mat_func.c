#include <math.h>
#include <stdlib.h>

#include "mat_func.h"
#include "math_func.h"

/*
 * return an init matrix, init with 0
 */
matrix_t *mat_create(int h, int w)
{
  matrix_t *res = NULL;
  res = malloc(sizeof(matrix_t));
  res->mat = calloc(sizeof(double), h * w);
  res->output = calloc(sizeof(double), w);
  res->height = h;
  res->width = w;

  return res;
}

void mat_free(matrix_t *mat)
{
  free(mat->mat);
  free(mat->output);
  free(mat);
}

matrix_t *mat_mult(matrix_t *mat1, matrix_t *mat2)
{
  int h = mat1->height, c = mat1->width, w = mat2->width;
  matrix_t *res = mat_create(h, w);

  for(int i = 0; i < w; ++i)
    for(int j = 0; j < h; ++j)
      for(int k = 0; k < c; ++k)
	res->mat[j*mat2->width + i] += mat1->mat[j*mat1->width + k] * mat2->mat[k*mat2->width + i];

  return res;
}

/*
 * Fill with random double matr
 */
void mat_rand(matrix_t *matr)
{
  for(int i = 0 ; i < matr->height * matr->width; ++i)
    matr->mat[i] = (rand() % 100 * 1.0) / 100.0 - 0.5;
}

void mat_activation(matrix_t *mat)
{
  for(int i = 0; i < mat->width * mat->height; ++i)
    mat->mat[i] = sigmoid(mat->mat[i]);
}
