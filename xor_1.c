#include <stdlib.h>
#include <stdio.h>

typedef struct neuron neuron;

struct neuron
{
    int weight[2];
    int size;
    int biais;
    int exit;
};

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

	output.exit -= output.biais;
}

neuron* neuron_init(neuron tab[])
{
	for (int i = 0; i < 2; ++i)
	{
		tab[i].weight[0] = rand()%100;
		tab[i].weight[1] = rand()%100;
		tab[i].size = 2;
	}
	return tab;	
}
