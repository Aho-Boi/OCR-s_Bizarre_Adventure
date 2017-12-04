#include "mat_func.h"

/*
 * return an init matrix, init with 0
 */
matrix_t *mat_create(int h, int w)
{
  matrix_t *res = NULL;
  res = malloc(sizeof(matrix_t))
  res->mat = calloc(sizeof(double), h * w);
  res->height = h;
  res->width = w;

  return res;
}

inline
void *mat_free(matrix_t mat)
{
  free(mat->mat);
  free(mat);
}

matrix_t *mat_mult(matrix_t *mat1, matrix_t *mat2)
{
  int h = mat1->height - 1, c = mat1->witdh, w = mat2->witdh;
  matrix_t *res = mat_create(h + 1, w);

  for(int i = 0; i < h; ++i)
    for(int j = 0; j < c; ++j)
      for(int k = 0; k < w; ++k)
	res->mat[i*w + j] += mat1->mat[i*c + k] * mat2->mat[k*w + j];

  return res;
}

/*
 * Fill with random double matr
 */
void mat_rand(matrix_t *matr)
{
  for(int i = 0 ; i < matr->height * matr->width; i++)
    matr->mat[i] = (rand() % 100 * 1.0) / 100.0 - 0.5;
}
