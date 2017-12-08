#include <math.h>
#include <stdlib.h>

#include "mat_func.h"

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
  int h = mat1->height - 1, c = mat1->width, w = mat2->width;
  matrix_t *res = mat_create(h + 1, w);

  for(int i = 0; i < h; ++i)
    for(int j = 0; j < w; ++j)
      for(int k = 0; k < c; ++k)
	res->mat[i*w + j] += mat1->mat[i*c + k] * mat2->mat[k*w + j];

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

void mat_tanh(matrix_t *neuron)
{
  for(int i = 0; i < neuron->width; ++i)
    neuron->output[i] = tanh(neuron->output[i] + neuron->mat[i * (neuron->height - 1)]);
}
