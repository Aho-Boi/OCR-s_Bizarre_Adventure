#include <math.h>
#include <stdlib.h>

#include "mat_func.h"
#include "math_func.h"

void work(matrix_t *input, matrix_t *neuron, matrix_t *output)
{
  matrix_t *OH = mat_mult(input, neuron);
  neuron->output = OH->mat;
  mat_activation(neuron);
  matrix_t *out = mat_mult(OH, output);
  output->output = out->mat;
  mat_activation(output);
  free(OH->output);
  free(OH);
  free(out->output);
  free(out);
}

double back_prop(matrix_t *exp, matrix_t *input, matrix_t *neuron, matrix_t *output)
{
  double out;
  int errO = output->height - 1, errN = neuron->height - 1;
  int nbO = output->width, nbN = neuron->width;

  for(int i = 0; i < nbO; ++i) //erreur couche sortie
  {
    out = output->output[i];
    output->mat[errO + i * output->height] = (exp->mat[i] - out) * derivate(out) * 0.5;
  }
  for(int i = 0; i < nbO; ++i) //mise a jour poids intermediaire -> sortie
  {
    for(int j = 0; j < output->height - 1; ++j)
    {
      out = neuron->output[j];
      output->mat[i * output->height + j] += 0.5 * output->mat[errO + i * output->height] * out;

      if(output->mat[i * output->height + j] > 5.0)
	output->mat[i * output->height + j] = 5.0;
      else if(output->mat[i * output->height + j] < -5.0)
	output->mat[i * output->height + j] = -5.0;
    }
  }
  for(int i = 0; i < nbN; ++i) //erreur couche intermediaire
  {
    out = neuron->output[i];
    neuron->mat[errN + i * neuron->height] = 0.0;
    for(int j = 0; j < nbO; ++j)
      neuron->mat[errN + neuron->height * i] += output->mat[j * output->height + i] * output->mat[errO + j * output->height];
    neuron->mat[errN + neuron->height * i] *= derivate(out) * 0.5;
  }
  for(int i = 0; i < nbN; ++i) //mise a jour poids input -> intermediaire
  {
    for(int j = 0; j < neuron->height - 1; ++j)
    {
      out = input->mat[j];
      neuron->mat[i * neuron->height + j] += 0.5 * neuron->mat[errN + i * neuron->height] * out;

      if(neuron->mat[i * neuron->height + j] > 5.0)
	neuron->mat[i * neuron->height + j] = 5.0;
      else if(neuron->mat[i * neuron->height + j] < -5.0)
	neuron->mat[i * neuron->height + j] = -5.0;
    }
  }

  return 36.0;
}
