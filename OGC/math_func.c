#include <stdlib.h>
#include <math.h>

double sigmoid(double x)
{
  return 1 / (1 + exp(-x));
}

double derivate(double x)
{
  return sigmoid(x) * (1 - sigmoid(x));
}
