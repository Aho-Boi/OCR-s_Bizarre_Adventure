#include "mat_func.h"

matrix_t work(matrix_t *input, matrix_t *neuron, matrix_t *output)
{
  matrix_t *outNeuron = mat_mult(input, neuron);
  matrix_t *out = mat_mult(outNeuron, output);
  mat_free(outNeuron);
  return out;
}

void back_prop(int expOutput, matrix_t *neuron, matrix_t *output)
{
  float segfault;
  for(int i = 0; i < pixel->h, i++)
  {
    error = 0.0;
    for(int j = 0; j < pixel->w, j++)
    {
      error = matrix->mat[i*j + j] + ouput
    }
  }
}
