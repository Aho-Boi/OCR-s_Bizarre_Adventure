#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "xor_func.h"

#define _LENGTH_ 4

int main(int argc, char *argv[])
{
  if (argc < 2)
    errx(1, "Choose training(1) or generalization(2)");
  
  srand(time(NULL));

  neuron output;
  for(int i = 0; i < _LENGTH_; ++i)
    output.weight[i] = (rand() % 100 * 1.0) / 100.0 - 0.5;
  output.size = _LENGTH_;
  output.bias = (rand() % 100 * 1.0) / 100.0 - 0.5;

  neuron *hidden = neuron_init(_LENGTH_);

  if (*argv[1] == '1')
  {
    float localErr = 0.0;
    int line = 0;
    int input[] = {0, 0, 0,  
		   0, 1, 1,  
		   1, 0, 1,
		   1, 1, 0}; 
    
    for(int i = 0; i < 200; ++i)
    {
      for(int j = 0; j < 4; ++j)
      {
	line = rand() % 4;
	localErr = work(input, line, hidden, &output);
	adaptWoutput(localErr, hidden, &output);
	adaptWhidden(localErr, input, line, hidden, &output);
      }
      printf("localError : %f\n", localErr);
    }

    FILE *file = fopen("training", "w");
    fwriteP(hidden, output, file);
    fclose(file);
  }
  else if (*argv[1] == '2')
  {
    FILE *file = fopen("training", "r");
    char *content = malloc(1000*sizeof(char));
    freadP(content, 1000, file);
    loadWeight(hidden, &output, content);
    fclose(file);

    printf("Enter the test: ");
    int input[_LENGTH_] = {0, 0};
    scanf("%d %d", input, input + 1);
    work(input, 0, hidden, &output);
    printf("%f", output.exit);
  }
  else
    errx(1, "Argument invalide");
}
