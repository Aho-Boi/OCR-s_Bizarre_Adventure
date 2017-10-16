#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "xor_func.h"

#define _LENGTH_ 2
#define _ERROR_FINAL_ 0.00001

int main(int argc, char *argv[])
{
  if (argc < 2)
    errx(1, "Choose training(1) or generalization(2)");
  
  neuron output;
  output.weight[0] = (rand() % 100 * 1.0) / 100.0 - 0.5;
  output.weight[1] = (rand() % 100 * 1.0) / 100.0 - 0.5;
  output.size = 2;
  output.error = (rand() % 100 * 1.0) / 100.0 - 0.5;

  int len = _LENGTH_;
  neuron *hidden = neuron_init(len);

  if (*argv[1] == '1')
  {
    float localErr = 0.0;
    int line = 0;
    int input[] = {-1, -1, -1,  
		   -1, 1, 1,  
		   1, -1, 1,
		   1, 1, -1}; 
    
    for(int i = 0; i < 41; ++i)
    {
      work(input, line, hidden, &output);
      localErr = localError(input, hidden, line, &output);
      printf("localError : %f\n", localErr);
      //prop_error_back(hidden, &output);
      weight_ajust(input, line, hidden, &output, localErr);
      line = rand() % 4;
    }

    FILE *file = fopen("training", "w");
    fwriteP(hidden, output, file);
    fclose(file);
  }
  else if (*argv[1] == '2')
  {
    FILE *file = fopen("training", "r");
    char *content = malloc(100*sizeof(char));
    freadP(content, 100, file);
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
