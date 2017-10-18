#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _LENH_ 2

typedef struct neuron neuron;

struct neuron
{
  float weight[_LENH_];
  int size;
  float bias;
  float exit;
};

int strlenP(const char *str)
{
  const char *s;
 
  for (s = str; *s; ++s);
  return (s - str);
}

float derivate(float x)
{
  return 1 - x * x;
}

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

void adaptWeight(float error, int *input, int lines, neuron *hidden, neuron *output)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    output->weight[i] -= 0.07 * error * hidden[i].exit;
    
    output->weight[i] = (output->weight[i] > 5.0) ? 5.0 : output->weight[i];
    output->weight[i] = (output->weight[i] < -5.0) ? -5.0 : output->weight[i];
  }
  
  for(int i = 0; i < _LENH_; ++i)
  {
    for(int j = 0; j < hidden[i].size; ++j)
    {
      float wChange = derivate(hidden[i].exit);
      wChange *= output->weight[i] * error * 0.7 * input[j + lines*3];
      hidden[i].weight[j] -= wChange; 
    }
    hidden[i].bias -= derivate(hidden[i].exit) * output->weight[i] * error *0.7;
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
    fprintf(file, " %g\n", hidden[i].bias);
  }
  for(int i = 0; i < _LENH_; ++i)
    fprintf(file, " %g", output.weight[i]);
  fprintf(file, " %g\n", output.bias);
}

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
