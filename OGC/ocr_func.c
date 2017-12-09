#include <math.h>
#include <stdlib.h>

#include "mat_func.h"
#include "math_func.h"

void work(matrix_t *input, matrix_t *neuron, matrix_t *output)
{
  matrix_t *OH = mat_mult(input, neuron);
  mat_activation(OH);
  neuron->output = OH->mat;
  matrix_t *out = mat_mult(OH, output);
  mat_activation(out);
  output->output = out->mat;
  free(OH->output);
  free(OH);
  free(out->output);
  free(out);
}

double back_prop(matrix_t *exp, matrix_t *neuron, matrix_t *output)
{
  double out;
  int errO = output->height - 1, errN = neuron->height - 1;
  int nbO = output->width, nbN = neuron->width;

  for(int i = 0; i < nbO; ++i) //erreur couche sortie
  {
    out = output->output[i];
    output->mat[errO * (i + 1)] = (out - exp->mat[i]) * derivate(out);
  }
  for(int i = 0; i < nbO; ++i) //mise a jour poids intermediaire -> sortie
  {
    for(int j = 0; j < output->height - 1; ++j)
    {
      out = output->output[i];
      output->mat[i * output->height + j] -= output->mat[errO * (i + 1)] * out;
    }
  }
  for(int i = 0; i < nbN; ++i) //erreur couche intermediaire
  {
    out = neuron->output[i];
    neuron->mat[errN * (i + 1)] = 0.0;
    for(int j = 0; j < nbO; ++j)
      neuron->mat[errN * (i + 1)] += output->mat[j * output->height + i] * output->mat[errO * (j + 1)];
    neuron->mat[errN * (i + 1)] *= derivate(out);
  }
  for(int i = 0; i < nbN; ++i) //mise a jour poids input -> intermediaire
  {
    for(int j = 0; j < neuron->height - 1; ++j)
    {
      out = neuron->output[i];
      neuron->mat[i * neuron->height + j] -= neuron->mat[errN * (i + 1)] * out;
    }
  }

  return 36.0;
}
