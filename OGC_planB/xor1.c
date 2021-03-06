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
double derivate(double x)
{
  return 1 - x * x;
}

// update neuron.exit of each neuron of hidden layer and of output 
// and return error of the patern
double work (int *input, int exp, neuron *hidden, neuron *output)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    hidden[i].exit = 0.0;
    for(int j = 0; j < _LENI_; ++j)
      hidden[i].exit += input[j] * hidden[i].weight[j];
    hidden[i].exit = tanh(hidden[i].exit + hidden[i].bias);
  }
  for(int i = 0; i < _LENO_; ++i)
  {
    output[i].exit = 0.0;
    for(int j = 0; j < _LENH_; ++j)
      output[i].exit += input[j] * output[i].weight[j];
    //output[i].exit = tanh(output[i].exit + output[i].bias);
  }
  
  return output->exit - exp;
}

// return an array of initialize neuron
neuron* neuron_init(int lengthAr, int lengthW)
{
  neuron *tab = malloc(lengthAr * sizeof(neuron));

  for (int i = 0; i < lengthAr; ++i)
  {
    tab[i].weight = malloc(lengthW * sizeof(double))
    for(int j = 0; j < lengthW; ++j)
      tab[i].weight[j] = (rand() % 100 * 1.0) / 100.0 - 0.5;
    tab[i].bias = (rand() % 100 * 1.0) / 100.0 - 0.5;
    tab[i].size = lengthW;
  }

  return tab;
}

// back propagation of the error
void adaptWeight(double e, int *input, int exp, neuron *hidden, neuron *output)
{
  for(int j = 0; i < _LENO_; ++j)
  {
    for(int i = 0; i < _LENH_; ++i)
    {
      output[j]->weight[i] -= 0.07 * e * hidden[i].exit;

      output[j]->weight[i] = (output[j]->weight[i] > 5.0) ? 5.0 : output[j]->weight[i];
      output[j]->weight[i] = (output[j]->weight[i] < -5.0) ? -5.0 : output[j]->weight[i];
    }
  }

  for(int i = 0; i < _LENH_; ++i)
  {
    double w = 0.0;
    for(int k = 0; k < _LENO_; ++k)
      w += output[k]->weight[i];    
    
    for(int j = 0; j < hidden[i].size; ++j)
    {
      double wChange = derivate(hidden[i].exit);
      wChange *= w * e * 0.7 * input[j];
      hidden[i].weight[j] -= wChange;
    }
    hidden[i].bias -= derivate(hidden[i].exit) * w * e * 0.7;
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
  for(int i = 0; i < _LENO_; ++i)
  {
    for(int w = 0; w < output[i].size; ++w)
    {
      fprintf(file, " %g", output[i].weight[w]);
    }
    fprintf(file, " %g\n", output[i].bias);
  }  
}

// parse weight and bias contained in weight and return it in double
double parseWeight(int i, char *weight)
{
  double result = 0.0;
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
  wi = 0, ni = 0;
  for(; i < length && ni < _LENO_; ++i)
  {
    if(weight[i] == ' ')
    {
      if (wi == output[ni].size)
	output[ni].bias = parseWeight(i + 1, weight);
      else
	output[ni].weight[wi] = parseWeight(i + 1, weight);
      wi += 1;
    }
    else if (weight[i] == '\n')
    {
      ni += 1;
      wi = 0;
    }
  }
}
