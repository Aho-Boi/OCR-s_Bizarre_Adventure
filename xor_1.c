#include <stdlib.h>
#include <stdio.h>

void work (int *input, neuron *hidden, neuron output)
{
	for(int i = 0; i < 2; ++i)
	{
		hidden[i].exit = input[0] * hidden[i].weight[0] + input[1] * hidden[i].weight[1] - hidden[i].biais; 
	}

	for(int i = 0; i < 2; i++)
	{
		output.exit += hidden[i].exit * output.weight[i]; 
	}

	output.exit -= output.biais
}
