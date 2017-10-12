#ifndef _XOR_FUNC_
#define -XOR_FUNC_

struct neuron
{
  float weight[2];
  int size;
  float error;
  float output;
};

float activation(float value);
void work (int *input, neuron *hidden, neuron output);
neuron* neuron_init(neuron tab[]);
void prop_error_back(neuron *hidden, neuron output, int size_tab);
float finalError (int *input, neuron output);
void weight_ajust (neuron *hidden, neuron output);
void freadP(char *str, int length, FILE *file);
void fwriteP(FILE *file);
float parseweight(int i, char *weight);  
void loadWeight(neuron *hidden, neuron output, char *weight);

#endif
