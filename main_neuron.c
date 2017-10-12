#include <stdio.h>
#include <stdlib.h>

#include "xor_func.h"

#define _LENGTH_ 2
#define _ERROR_FINAL_ 0.5

int main(void)
{
  float finalErr = 0.0;
  int line = 0;
  int input[] = {0, 0, 0,  
                 0, 1, 1,  
                 1, 0, 1,
                 1, 1, 0}; 
  neuron hidden[_LENGTH_] = neuron_init(_LENGTH_);
  
  neuron output;
  output.weight[0] = (rand() % 100 * 1.0) / 100.0;
  output.weight[1] = (rand() % 100 * 1.0) / 100.0;
  output.size = 2;
  output.error = (rand() % 100 * 1.0) / 100.0;

  do
  {
    work(input, line, hidden, output);
    finalErr = finalError(input, line, output);
    prop_error_back(hidden, output);
    weight_ajust(hidden, output);
    line++;
  } while(finalErr > _ERROR_FINAL_);

  FILE file = fopen("training", "w");
  fwriteP(hidden, putput, file);
  fclose(file);
}
