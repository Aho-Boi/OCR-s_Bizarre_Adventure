
# include <stdlib.h>
# include <stdio.h>

struct neuron
{
    float weight[2];
    int size = 2 ;
    float biais;
    int exit;
};

neuron* neuron_init(neuron tab[])
       	{
	    tab[0].weight[0] = rand()%100;
	    tab[1].weight[1] = rand()%100;
	    return tab[]	
	}	
