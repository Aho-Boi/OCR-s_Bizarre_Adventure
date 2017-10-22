#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "xor_func.h"

// return length of str
int strlenP(const char *str)
{
  const char *s;

  for (s = str; *s; ++s);
  return (s - str);
}

// return derivate of tanh(x)
float derivate(float x)
{
  return 1 - x * x;
}

// update neuron.exit of each neuron of hidden layer and of output 
// and return error of the patern
float work (int *input, int lines, neuron *hidden, neuron *output)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    hidden[i].exit = 0.0;
    for(int j = 0; j < _LENH_; ++j)
      hidden[i].exit += input[j + 3*lines] * hidden[i].weight[j];
    hidden[i].exit = tanh(hidden[i].exit + hidden[i].bias);
  }

  output->exit = 0.0;
  for(int i = 0; i < _LENH_; ++i)
    output->exit += hidden[i].exit * output->weight[i];
  return output->exit - input[2 + lines*3];
}

// return an array of initialize neuron
neuron* neuron_init(int length)
{
  neuron *tab = malloc(length * sizeof(neuron));

  for (int i = 0; i < _LENH_; ++i)
  {
    for(int j = 0; j < _LENH_; ++j)
      tab[i].weight[j] = (rand() % 100 * 1.0) / 100.0 - 0.5;
    tab[i].bias = (rand() % 100 * 1.0) / 100.0 - 0.5;
    tab[i].size = _LENH_;
  }

  return tab;
}

// back propagation of the error
void adaptWeight(float e, int *input, int lines, neuron *hidden, neuron *output)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    output->weight[i] -= 0.07 * e * hidden[i].exit;

    output->weight[i] = (output->weight[i] > 5.0) ? 5.0 : output->weight[i];
    output->weight[i] = (output->weight[i] < -5.0) ? -5.0 : output->weight[i];
  }

  for(int i = 0; i < _LENH_; ++i)
  {
    for(int j = 0; j < hidden[i].size; ++j)
    {
      float wChange = derivate(hidden[i].exit);
      wChange *= output->weight[i] * e * 0.7 * input[j + lines*3];
      hidden[i].weight[j] -= wChange;
    }
    hidden[i].bias -= derivate(hidden[i].exit) * output->weight[i] * e *0.7;
  }
}

// read length character file an save them in str
void freadP(char *str, int length, FILE *file)
{
  int i = 0;

  do
  {
    str[i] = fgetc(file);
    i++;
  } while(i < length && str[i - 1] != EOF);
  str[i - 1] = 0;
}

// write in file weight and bias of each neuron
void fwriteP(neuron *hidden, neuron output, FILE *file)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    for(int w = 0; w < hidden[i].size; ++w)
    {
      fprintf(file, " %g", hidden[i].weight[w]);
    }
    fprintf(file, " %g\n", hidden[i].bias);
  }
  for(int i = 0; i < _LENH_; ++i)
    fprintf(file, " %g", output.weight[i]);
  fprintf(file, " %g\n", output.bias);
}

// parse weight and bias contained in weight and return it in float
float parseWeight(int i, char *weight)
{
  float result = 0.0;
  int coma = 0, sign = 1;

  for(; weight[i] != ' ' && weight[i] != '\n'; ++i)
  {
    if (weight[i] == '.')
    {
      coma = 1;
    }
    else if(weight[i] == '-')
      sign = -1;
    else
    {
      result = result * 10.0 + (weight[i] - '0') * 1.0;
      coma += (!coma) ? 0 : 1;
    }
  }
  for(; coma > 1; --coma)
    result /= 10;
  return result * sign;
}

// load weight and bias in each neuron
void loadWeight(neuron *hidden, neuron *output, char *weight)
{
  int length = strlenP(weight);
  int wi = 0, ni = 0, i = 0;
  for(; i < length && ni < _LENH_; ++i)
  {
    if(weight[i] == ' ')
    {
      if (wi == hidden[ni].size)
	hidden[ni].bias = parseWeight(i + 1, weight);
      else
	hidden[ni].weight[wi] = parseWeight(i + 1, weight);
      wi += 1;
    }
    else if (weight[i] == '\n')
    {
      ni +=1;
      wi = 0;
    }
  }
  wi = 0;
  for(; i < length && weight[i] != '\n'; ++i)
  {
    if(weight[i] == ' ')
    {
      if (wi == output->size)
	output->bias = parseWeight(i + 2, weight);
      else
	output->weight[wi] = parseWeight(i + 1, weight);
      wi += 1;
    }
  }
}
