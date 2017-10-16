#ifndef _XOR_FUNC_
#define _XOR_FUNC_

typedef struct neuron neuron;

struct neuron
{
  float weight[2];
  int size;
  float error;
  float exit;
};

int strlenP(const char *str);
float activation(float value);
void work (int *input, int lines, neuron *hidden, neuron *output);
neuron* neuron_init(int length);
void prop_error_back(neuron *hidden, neuron *output);
float localError (int *input, neuron *hidden, int lines, neuron *output);
void weight_ajust (int *input, int lines, neuron *hidden, neuron *output, int localError);
void freadP(char *str, int length, FILE *file);
void fwriteP(neuron *hidden, neuron output, FILE *file);
float parseWeight(int i, char *weight);  
void loadWeight(neuron *hidden, neuron *output, char *weight);

#endif
