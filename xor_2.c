#include <stdlib.h>
#include <stdio.h>

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
