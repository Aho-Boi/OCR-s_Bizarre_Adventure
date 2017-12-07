#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "mat_func.h"

static
void mat_write(matrix_t *mat, FILE *file)
{
  fseek(file, 0, SEEK_END);
  for(int i = 0; i < mat->height; ++i)
  {
    for(int j = 0; j < mat->width; ++j)
      fprintf(file, " %8g", mat->mat[i * mat->width + j]);
    fprintf(file, "\n");
  }
  fprintf(file, "LOLI!!!\n");
}

void my_write(matrix_t *neuron, matrix_t *output, char *cfile)
{
  FILE *file = fopen(cfile, "w");
  mat_write(neuron, file);
  mat_write(output, file);
  fclose(file);
}

static
char* read_word(size_t* i, char* content, size_t size)
{
  char *res = calloc(sizeof(char), 9);

  for(int j = 0; *i < size && content[*i] != ' ' && content[*i] != '\n'; ++i, ++j)
    res[j] += content[*i];
  (*i)++;

  return res;
}

int cmpstring(char* a , char* b)
{
  int res = 0;
  for(int i=0; a[i] == b[i] ; i++ )
  {
    res = 1;
  }
  return res;
}

static
void mat_read(size_t* i, char* content, size_t size, matrix_t *mat)
{
  char *word = read_word(i, content, size);
  double *m = mat->mat;
  char *stru = "LOLI!!!";
  do 
  {
    *m = atof(word);
    m++;
    word = read_word(i, content, size);
  } while(cmpstring(word,stru) != 1);
}

void my_read(matrix_t *neuron, matrix_t *output, char *cfile)
{
  FILE *file = fopen(cfile, "r");
  if(!file)
  {
    fclose(file);
    return ;
  }
  struct stat loli;
  stat(cfile, &loli);
  size_t size = loli.st_size - 1;;
  char *content = malloc(sizeof(char) * size);
  fread(content, sizeof(char), size, file);
  fclose(file);

  size_t i = 0;
  mat_read(&i, content, size, neuron);
  mat_read(&i, content, size, output);
}
