#include <stdio.h>
#include <stdlib.h>

#include "xor_func.h"

#define _ERROR_FINAL_ 0.5

int main(void)
{
  float finalErr = 0.0;
  do
  {
    work(input, hidden, output);
    finalErr = finalError(input, output);
    prop_error_back(hidden, output, lenH);
    weight_ajust(hidden, output);
  } while(finalErr > _ERROR_FINAL_);
}
