#include <stdlib.h>
#include <stdio.h>
#include "xor_1.c"

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

