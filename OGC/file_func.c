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
      fprintf(file, " %8g", mat->mat[i * mat->width + j]);
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
char* read_word(int* i, char* content, size_t size)
{
  char *res = calloc(sizeof(char), 9);

  for(int j = 0; i < size && content[i] != ' ' && content[i] != '\n'; ++i, ++j)
    res[j] += content[i];
  i++;

  return res;
}

static
void mat_read(int* i, char* content, size_t size, matrix_t *mat)
{
  char *word = read_word(&i, content, size);
  double m = mat->mat;
  do 
  {
    *m = atof(word);
    m++;
    word = read_word(&i, content, size);
  } while(word != "LOLI!!!");
}

void read(matrix_t *neuron, matrix_t *output, char *cfile)
{
  FILE *file = fopen(cfile, "r");
  if(!file)
  {
    fclose(file);
    return ;
  }
  size_t size = fsize(file);
  char *content = malloc(sizeof(char) * size);
  fread(content, sizeof(char), size, file);
  fclose(file;)

  int i = 0;
  mat_read(&i, content, size, neuron);
  mat_read(&i, cotnent, size, output);
}
