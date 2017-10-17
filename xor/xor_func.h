#ifndef _XOR_FUNC_
#define _XOR_FUNC_

#define _LENGTH_ 4

typedef struct neuron neuron;

struct neuron
{
  float weight[_LENGTH_];
  int size;
  float bias;
  float exit;
};

int strlenP(const char *str);
float activation(float value);
float work (int *input, int lines, neuron *hidden, neuron *output);
neuron* neuron_init(int length);
void adaptWoutput(float error, neuron *hidden, neuron *output);
void adaptWhidden(float error, int *input, int lines, neuron *hidden, neuron *output);
void freadP(char *str, int length, FILE *file);
void fwriteP(neuron *hidden, neuron output, FILE *file);
float parseWeight(int i, char *weight);  
void loadWeight(neuron *hidden, neuron *output, char *weight);

#endif
