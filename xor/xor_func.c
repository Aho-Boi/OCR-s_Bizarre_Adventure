#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _LENH_ 2

typedef struct neuron neuron;

struct neuron
{
  float weight[2];
  int size;
  float error;
  float exit;
};

int strlenP(const char *str)
{
  const char *s;
 
  for (s = str; *s; ++s);
  return (s - str);
}

float activation(float value)
{
  return (value > 0.0) ? 1.0 : 0.0;
}

void work (int *input, int lines, neuron *hidden, neuron *output)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    hidden[i].exit = 0.0;
    for(int j = 0; j < _LENH_; ++j)
      hidden[i].exit += input[j + 3*lines] * hidden[i].weight[j];
    hidden[i].exit = tanh(hidden[i].exit + hidden[i].error); 
  }

  output->exit = 0.0;
  for(int i = 0; i < _LENH_; ++i)
    output->exit += hidden[i].exit * output->weight[i]; 
  //	output->exit = output->exit + output->error;
}

neuron* neuron_init(int length)
{
  neuron *tab = malloc(length * sizeof(neuron));

  for (int i = 0; i < _LENH_; ++i)
  {
    for(int j = 0; j < _LENH_; ++j)
    {
      tab[i].weight[j] = (rand() % 100 * 1.0) / 100.0 - 0.5;
    }
    tab[i].error = (rand() % 100 * 1.0) / 100.0 - 0.5;
    tab[i].size = _LENH_;
  }
  
  return tab;  
}

void prop_error_back(neuron *hidden, neuron *output)
{
  float error;
  for(int i = 0; i < _LENH_; ++i)
  {
    error = 0.0;
    for(int j = 0; j < hidden[i].size; ++j)
    {
      error = output->error * hidden[i].weight[j];
      hidden[i].error += error * hidden[i].exit;
    }
  }
}

float localError (int *input, neuron *hidden, int lines, neuron *output)
{
  float localError = (1.0 * input[_LENH_ + lines*3]) - output->exit;
  float wch = 0.0;

  for(int i = 0; i < _LENH_; ++i)
  {
    wch = 0.07 * localError * hidden[i].exit;
    output->weight[i] -= wch;

    if(output->weight[i] > 5.0)
      output->weight[i] = 5.0;
    else if(output->weight[i] < -5.0)
      output->weight[i] = -5.0;
  }
  output->error *= localError;

  return localError;
}

void weight_ajust (int *input, int lines, neuron *hidden, neuron *output, float localError)
{
  for (int i = 0; i < _LENH_; ++i)
  {
    for(int j = 0; j < hidden[i].size; ++j)
    {
      double x = 1.0 - (hidden[i].exit * hidden[i].exit);
      x = x * output->weight[i] * localError * 0.7;
      x *= input[j * 3*lines];
      hidden[i].weight[j] -= x; 
    }
  }
}

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

void fwriteP(neuron *hidden, neuron output, FILE *file)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    for(int w = 0; w < hidden[i].size; ++w)
    {
      fprintf(file, " %g", hidden[i].weight[w]);
    }
    fprintf(file, "\n");
  }
  fprintf(file, " %g %g\n", output.weight[0], output.weight[1]);
}

float parseWeight(int i, char *weight)
{
  float result = 0.0;
  int coma = 0, sign = 1;

  for(; weight[i] != ' '; ++i)
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

void loadWeight(neuron *hidden, neuron *output, char *weight)
{
  int length = strlenP(weight);
  int wi = 0, ni = 0, i = 0;
  for(; i < length && ni < _LENH_; ++i)
  {
    if(weight[i] == ' ')
    {
      hidden[ni].weight[wi] = parseWeight(i + 1, weight);
      printf("%f\n", hidden[ni].weight[wi]);
      wi += 1;
    }  
    else if (weight[i] == '\n')
    {
      ni +=1;
      wi = 0;
    }
  }
  for(int w = 0; w < output->size; ++w)
    output->weight[w] = parseWeight(i + 1, weight);
}
