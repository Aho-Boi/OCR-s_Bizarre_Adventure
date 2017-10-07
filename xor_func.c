#include <stdlib.h>
#include <stdio.h>

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

void work (int *input, neuron *hidden, neuron output)
{
	for(int i = 0; i < 2; ++i)
	{
		hidden[i].exit = activation(input[0] * hidden[i].weight[0] + input[1] * hidden[i].weight[1] - hidden[i].error); 
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
		tab[i].weight[0] = rand()%100 * 1.0;
		tab[i].weight[1] = rand()%100 * 1.0;
		tab[i].error = rand()%100 * 1.0;
		tab[i].size = 2;
	}
	return tab;	
}

void prop_error_back(neuron *neural,neuron exit, int size_tab)
{
	float fail;
	for(int i = 0; i < size_tab; ++i)
	{
		fail = exit.error;
		neural[i].error += fail * neural[i].weight[0];
	        neural[i].error += fail * neural[i].weight[1];
	        neural[i].error *= neural[i].exit
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
