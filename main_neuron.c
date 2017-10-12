#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "xor_func.h"

#define _LENGTH_ 2
#define _ERROR_FINAL_ 0.5

int main(int argc, char *argv[])
{
  if (argc < 2)
    errx(1, "Choose training(1) or generalization(2)");
  if (argv[1] == "1")
  {
    float finalErr = 0.0;
    int line = 0;
    int input[] = {0, 0, 0,  
		   0, 1, 1,  
		   1, 0, 1,
		   1, 1, 0}; 
    int len = _LENGTH_;
    neuron *hidden = neuron_init(len);
    
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

    FILE *file = fopen("training", "w");
    fwriteP(hidden, output, file);
    fclose(file);
  }
  else if (argv[1] == '2')
  {
    //FIX ME  
  }
  else
    errx(1, "Argument invalide");
}
