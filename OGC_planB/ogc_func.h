#ifndef _XOR_FUNC_
#define _XOR_FUNC_

#define _LENI_ 256
#define _LENH_ 25
#define _LENO_ 1
#define _NB_INPUT_ 3
#define _NB_TURN_ 8000

typedef struct neuron neuron;

struct neuron
{
  double *weight;
  int size;
  double bias;
  double exit;
};

int strlenP(const char *str);
double derivate(double x);
double work (int *input, int exp, neuron *hidden, neuron *output);
neuron* neuron_init(int lengthAr, int lengthW);
void adaptWeight(double e,int *input, neuron *hidden, neuron *output);
void freadP(char *str, int length, FILE *file);
void fwriteP(neuron *hidden, neuron *output, FILE *file);
double parseWeight(int i, char *weight);  
void loadWeight(neuron *hidden, neuron *output, char *weight);

#endif
