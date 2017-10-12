#include <stdlib.h>
#include <stdio.h>

#define _LENH_ 2

typedef struct neuron neuron;

struct neuron
{
  float weight[2];
  int size;
  float error;
  float exit;
};

float activation(float value)
{
  return (value > 0.0) ? 1.0 : 0.0;
}

void work (int *input, int lines, neuron *hidden, neuron output)
{
  for(int i = 0; i < _LENH_; ++i)
  {
    hidden[i].exit = 0.0;
    for(int j = 0; j < _LENH_; ++j)
      hidden[i].exit += input[j + 3*lines] * hidden[i].weight[j];
    hidden[i].exit -= hidden[i].error; 
  }

  output.exit = 0.0;
  for(int i = 0; i < _LENH_; ++i)
    output.exit += hidden[i].exit * output.weight[i]; 
  output.exit = activation(output.exit + output.error);
}

neuron* neuron_init(int length)
{
  neuron tab[length];

  for (int i = 0; i < _LENH_; ++i)
  {
    for(int j = 0; j < _LENH_; ++j)
      tab[i].weight[j] = (rand() % 100 * 1.0) / 100.0;
    tab[i].error = (rand() % 100 * 1.0) / 100.0;
    tab[i].size = _LENH_;
  }
  return tab;  
}

void prop_error_back(neuron *hidden, neuron output)
{
  float fail;
  for(int i = 0; i < _LENH_; ++i)
  {
    fail = output.error;
    for(int j = 0; j < _LENH_; ++j)
      hidden[i].error += fail * hidden[i].weight[j];
    hidden[i].error *= hidden[i].exit;
  }
}

float finalError (int *input, int lines, neuron output)
{
  float localError = (1.0 * input[_LENH_ + lines*3]) - output.exit;

  output.error *= localError;

  return 0.5 * localError* localError;
}

void weight_ajust (neuron *hidden, neuron output)
{
  for (int i = 0; i < _LENH_; ++i)
  {
    for(int j = 0; j < _LENH_; ++j)
    {
      hidden[i].weight[j] = output.error * hidden[i].exit;
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
  } while(i < length && str[i - 1] != 'EOF');
  
  str[i - 1] = 0;
  return str;
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

void loadWeight(neuron *hidden, int lenH, neuron output, char *weight)
{
  int length = strlen(weight);
  int wi = 0, ni = 0;
  for(int i = 0; i < length; ++i)
  {
    if(weight[i] == ' ')
    {
      if (ni >= lenH)
	output.weight[wi] = parseWeight(i + 1, weight);
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
}

float parseweight(int i, char *weight)
{
  float result = 0.0;
  int coma = 0;

  for(; weight[i] != ' '; ++i)
  {
    if (weight[i] = '.')
    {
      coma = 1;
    }
    else
    {
      result = result * 10.0 + (weight[i] - '0') * 1.0;
      coma += (!coma) ? 0 : 1;
    }
  }
  return result / (10 * (coma - 1));
}

