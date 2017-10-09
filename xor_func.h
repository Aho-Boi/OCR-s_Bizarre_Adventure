#ifndef _XOR_FUNC_
#define -XOR_FUNC_

struct neuron
{
	float weight[2];
        int size;
        float error;
        float exit;
};

float activation(float value);
void work (int *input, neuron *hidden, neuron output);
neuron* neuron_init(neuron tab[]);
void prop_error_back(neuron *neural,neuron exit, int size_tab);
float finalError (int *input, neuron output);
void weight_ajust (neuron *hidden, neuron output);
void freadP(char *str, int length, FILE *file);

#endif
