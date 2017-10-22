#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "xor_func.h"

#define _LENH_ 2

int main(int argc, char *argv[])
{
  if (argc < 2)
    errx(1, "Choose training(1) or generalization(2)");

  srand(time(NULL));

  neuron output;
  for(int i = 0; i < _LENH_; ++i)
    output.weight[i] = (rand() % 100 * 1.0) / 100.0 - 0.5;
  output.size = _LENH_;
  output.bias = (rand() % 100 * 1.0) / 100.0 - 0.5;

  neuron *hidden = neuron_init(_LENH_);

  // training
  if (*argv[1] == '1')
  {
    float localErr = 0.0;
    double totalErr = 0.0, save = 0.0;
    int line = 0, count = 1;
    int input[] = {0, 0, 0,
		   0, 1, 1,
		   1, 0, 1,
		   1, 1, 0};

    do
    {
      save = totalErr;
      for(int j = 0; j < 4; ++j)
      {
	localErr = work(input, line, hidden, &output);
	int i1 =input[line*3], i2 = input[line*3 + 1];
	float oe = output.exit;
	printf("%d xor %d = %f : LocalErr = %f\n", i1, i2, oe, localErr);
	adaptWeight(localErr, input, line, hidden, &output);
	totalErr += localErr;
	line++;
	if (line == 4)
	  line = 0;
      }
      printf("Total error : %g\n", totalErr/count);
      count += 1;
    }while(totalErr != save || totalErr/count < 0.0);

    FILE *file = fopen("training", "w");
    fwriteP(hidden, output, file);
    fclose(file);
  }
  // generalization
  else if (*argv[1] == '2')
  {
    FILE *file = fopen("training", "r");
    char *content = malloc(1000*sizeof(char));
    freadP(content, 1000, file);
    loadWeight(hidden, &output, content);
    fclose(file);

    printf("Enter the test: ");
    int input[3] = {0, 0, 0};
    scanf("%d %d", input, input + 1);
    work(input, 0, hidden, &output);
    printf("%f", output.exit);
  }
  else
  {
    free(hidden);
    errx(1, "Invalid argument");
  }

  free(hidden);
}
