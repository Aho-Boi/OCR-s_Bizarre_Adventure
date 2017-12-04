#include<stdio.h>
#include<stdlib.h>
#include "mat_func.h"

static
void mat_write(matrix_t *mat, FILE *file)
{
  fseek(file, 0, SEEK_END);
  for(int i = 0; i < mat->height; ++i)
  {
    for(int j = 0; j < mat->witdh; ++j)
      fprintf(file, " %g", mat->mat[i * mat->width + j]);
    fprintf(file, "\n");
  }
  fprintf(file, "LOLI!!!\n");
}

void write(matrix_t *neuron, matrix_t *output, char *cfile)
{
  FILE *file = fopen(cfile, "w");
  mat_write(neuron, file);
  mat_write(output, file);
  fclose(file;)
}

static
void mat_read(matrix_t *mat, FILE *file)
{

}

void read(matrix_t *neuron, matrix_t *output, char *cfile)
{
  FILE *file = fopen(cfile, "r");
  mat_write(neuron, file);
  mat_write(output, file);
  fclose(file;)
}
