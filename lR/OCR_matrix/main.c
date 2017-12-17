#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main_func.h"

int main(int argc, char *argv[])
{
  if(argc < 2)
    errx(1, "Choose training(1) or generalization(2)");
  
  srand(time(NULL));

  if(*argv[1] == '1')
  {
    training("training");
  }
  else if(*argv[1] == '2')
  {
    generalization("training");
  }
}
