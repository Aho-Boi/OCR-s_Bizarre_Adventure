#include <stdlib.h>
#include <stdio.h>

typedef struct neuron neuron;

float activation(float value)
{
  return (value > 0.0) ? 1.0 : 0.0;
}

void work (int *input, neuron *hidden, neuron output)
{
  for(int i = 0; i < 2; ++i)
  {
    hidden[i].exit = input[0] * hidden[i].weight[0] + input[1] * hidden[i].weight[1] - hidden[i].error; 
  }

  for(int i = 0; i < 2; i++)
  {
    output.exit += hidden[i].exit * output.weight[i]; 
  }

  output.exit = activation(output.exit + output.error);
}

neuron* neuron_init(neuron tab[])
{
  for (int i = 0; i < 2; ++i)
  {
    tab[i].weight[0] = rand() % 100 * 1.0;
    tab[i].weight[1] = rand() % 100 * 1.0;
    tab[i].error = rand() % 100 * 1.0;
    tab[i].size = 2;
  }
  return tab;  
}

void prop_error_back(neuron *hidden, neuron output, int size_tab)
{
  float fail;
  for(int i = 0; i < size_tab; ++i)
  {
    fail = exit.error;
    hidden[i].error += fail * hidden[i].weight[0];
    hidden[i].error += fail * hidden[i].weight[1];
    hidden[i].error *= hidden[i].exit
  }
}

float finalError (int *input, neuron output)
{
  float localError = (1.0 * input[2]) - output.exit;

  output.error *= localError;

  return 0.5 * localError* localError;
}

void weight_ajust (neuron *hidden, neuron output)
{
  for (int i = 0; i < 2; ++i)
  {
    for(int j = 0; j < 2; ++j)
    {
      hidden[i].weight[k] = output.error * hidden[i].exit;
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
  } while(i < length && stri[i - 1] != 'EOF');
  
  str[i - 1] = 0;
  return str;
}

void fwriteP(neuron *hidden, int lenH, neuron output, FILE *file)
{
  for(int i = 0; i < lenH; ++i)
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
    else if (wheight[i] == '\n')
      ni +=1;
      wi = 0;
  }
}

float parseweight(int i, char *weight)
{
  float result = 0.0;
  int coma = 0;

  for(char i = weight; i != ' '; ++i)
  {
    if (i = '.')
    {
      coma = 1;
    }
    else
    {
      result = result * 10.0 + (*i - '0') * 1.0;
      coma += (!coma) ? 0 : 1;
    }
  }
  return result / (10 * (coma - 1));
}

