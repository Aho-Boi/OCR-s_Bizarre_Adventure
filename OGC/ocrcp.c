#include <math.h>
#include <stdlib.h>

#include "mat_func.h"

static inline
double derivate(double x)
{
  return 1 - x * x;
}

void work(matrix_t *input, matrix_t *neuron, matrix_t *output)
{
  neuron->output = mat_mult(input, neuron)->mat;
  mat_tanh(neuron);
  matrix_t *oN = mat_create(2, neuron->width);
  oN->mat = neuron->output;
  output->output = mat_mult(oN, output)->mat;
  free(oN->output);
  free(oN);
}

static
double final_err(int expOutput, matrix_t *output)
{
  double output_err = 0.0, err = 0.0;

  for(int i = 0; i < output->width; ++i)
  {
    err = (expOutput == i) - output->output[i];
    output->mat[i * output->width] = err * derivate(output->output[i]);
    output_err += 0.5 * err * err;
  }

  return output_err;
}

double back_prop(int expOutput, matrix_t *neuron, matrix_t *output)
{
  double err = final_err(expOutput, output), bias, d;

  for(int i = 0; i < output->width; ++i)
    for(int j = 0; j < output->height - 1; ++j)
    {
      output->mat[i * output->height + j] -= 0.07 * err * neuron->output[i];
      if(output->mat[i * output->height + j] > 5.0)
        output->mat[i * output->height + j] = 5.0;
      else if(output->mat[i * output->height + j] < -5.0)
        output->mat[i * output->height + j] = -5.0;
    }

  for(int i = 0; i < neuron->width; ++i)
  {
    for(int j = 0; j < neuron->height - 1; ++j)
    {
      bias = output->mat[i * (output->height - 1)];
      neuron->mat[i * neuron->height + j] -= 0.7 * bias * neuron->output[i];
    }
    d = derivate(neuron->output[i]);
    neuron->mat[i * (neuron->height - 1)] -= d * err * 0.7;
  }

  return err;
}
