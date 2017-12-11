#include <dirent.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_func.h"
#include "mat_func.h"
#include "my_string.h"
#include "ocr_func.h"
#include "load_picture.h"

#define _NB_NEURON_ 10
#define _NB_INPUT_ 25 	//5 * 5
#define _NB_OUTPUT_ 3
#define _NB_TRAINING_ 3

static
void picture_to_double(SDL_Surface *surface, matrix_t *input)
{
  for(int x = 0; x < surface->h; ++x)
    for(int y = 0; y < surface->w; ++y)
      input->mat[x * surface->w +y] = (getpixel(surface, x, y) != 0);
}

void test(input_t **input)
{

  double mat1[]     = {1.0, 0.0, 1.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0, 0.0,
			1.0, 0.0, 1.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0, 0.0,
			1.0, 0.0, 1.0, 0.0, 1.0};
  memmove((*input)->mat->mat, mat1, sizeof(double) * 25);

  double mat2[]           = {0.0, 1.0, 0.0, 1.0, 0.0,
      			      1.0, 0.0, 1.0, 0.0, 1.0,
			      0.0, 1.0, 0.0, 1.0, 0.0,
			      1.0, 0.0, 1.0, 0.0, 1.0,
			      0.0, 1.0, 0.0, 1.0, 0.0};
  memmove((*(input + 1))->mat->mat, mat2, sizeof(double) * 25);
 
  double mat3[]            = {0.0, 1.0, 1.0, 1.0, 0.0,
			      0.0, 1.0, 0.0, 1.0, 0.0,
			      0.0, 1.0, 0.0, 1.0, 0.0,
			      0.0, 1.0, 0.0, 1.0, 0.0,
			      0.0, 1.0, 1.0, 1.0, 0.0};
  memmove((*(input + 2))->mat->mat, mat3, sizeof(double) * 25);
/*
  double mat4[]            = {1.0, 0.0, 1.0, 0.0, 1.0,
			      0.0, 1.0, 0.0, 1.0, 0.0,
			      1.0, 0.0, 1.0, 0.0, 1.0,
			      0.0, 1.0, 0.0, 1.0, 0.0,
			      1.0, 0.0, 1.0, 0.0, 1.0};
  memmove((*(input + 3))->mat->mat, mat4, sizeof(double) * 25);
*/
}
static
input_t** loadInput(char* file)
{
  input_t **input = malloc(sizeof(input_t*) * _NB_TRAINING_);
  int i = 0;
  DIR *rep = opendir(file);
  if(!rep)
    errx(1, "Could not load image training");
  struct dirent *actual;

  while(i < _NB_OUTPUT_/*(actual = readdir(rep)) != NULL*/)
  {
    //if(actual->d_name[0] == '.')
    //  continue;
    *(input + i) = malloc(sizeof(input_t));
    (*(input + i))->mat = mat_create(1, _NB_INPUT_);
    //char* conc = my_strcon(file, actual->d_name);
    //picture_to_double(IMG_Load(conc), (*(input + i))->mat);
    (*(input + i))->expOutput = mat_create(1, _NB_OUTPUT_);
    //int l = atoi(actual->d_name);
    (*(input + i))->expOutput->mat[i] = 1;
    (*(input + i))->exp = i;
    i++;
  }
  test(input);
  return input;
}

static
void output_print(int exp, matrix_t *output)
{
  printf("RESULTAT FOR %d: \n", exp);
  for(double *m = output->output; m < output->output + output->width; ++m)
  {
    printf("%g ", *m);
  }
  printf("\n");
}

void training(char* file)
{
  input_t **input = loadInput("trainingPicture/");
  input_t *inp = NULL;
  matrix_t *neuron = mat_create(_NB_INPUT_ + 2, _NB_NEURON_);
  matrix_t *output = mat_create(_NB_NEURON_ + 2, _NB_OUTPUT_);
  mat_rand(neuron);
  mat_rand(output);
  my_read(neuron, output, file);

  double totalErr = 0.0, save = 0.0, localErr = 0.0;
  size_t count = 1;
  int j = 0;

  do
  {
    save = totalErr;
    for(int i = 0; i < _NB_TRAINING_; ++i)
    {
      j = rand() % _NB_TRAINING_;
      inp = *(input + j);
      work(inp->mat, neuron, output);
      localErr = back_prop(inp->expOutput, inp->mat, neuron, output);
      output_print(inp->exp, output);
      printf("ERR : %f\n", localErr);
      totalErr += localErr;
    }
    //printf("Total error : %g\n", totalErr);
    printf("%zu tours\n", count);
    count++;
    if(!(count % 999))
      my_write(neuron, output, "training");
  } while(count < 10000/*totalErr != save || totalErr/count < 0.0*/);
  my_write(neuron, output, "training");

  mat_free(neuron);
  mat_free(output);
}

void generalization(char *file)
{
  input_t **input = loadInput("generalization/");
  matrix_t *neuron = mat_create(_NB_INPUT_ + 1, _NB_NEURON_);
  matrix_t *output = mat_create(_NB_NEURON_ + 1, _NB_OUTPUT_);
  my_read(neuron, output, file);
  work(input[0]->mat, neuron, output);
  output_print(input[0]->exp, output);

  mat_free(neuron);
  mat_free(output);
}
