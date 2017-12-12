#include <stdlib.h>
#include <stdio.h>

int* zerofill(int* mat, int x, int y)
{
  int* res = malloc(sizeof(int) * 16 * 16);
  for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
      res[i * y + j] = mat[i * y + j];
  for(int k = x * y; k < 16 * 16; ++k)
    res[k] = 0;
  return res;
}

int main(void)
{
  int* loli = malloc(sizeof(int) * 3 * 5);
  for(int i = 0; i < 15; ++i)
    loli[i] = 1;
  int* l = zerofill(loli, 3, 5);
  for(int i = 0; i < 256; ++i)
    printf("%d ", l[i]);
  return 36;
}
  
