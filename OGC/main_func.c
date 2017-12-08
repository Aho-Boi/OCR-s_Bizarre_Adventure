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

#define _NB_NEURON_ 3
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

static
input_t** loadInput(char* file)
{
  input_t **input = malloc(sizeof(input_t*) * _NB_TRAINING_);
  int i = 0;
  DIR *rep = opendir(file);
  if(!rep)
    errx(1, "Could not load image training");
  struct dirent *actual;

  while((actual = readdir(rep)) != NULL)
  {
    if(actual->d_name[0] == '.')
      continue;
    *(input + i) = malloc(sizeof(input_t));
    (*(input + i))->mat = mat_create(5, 5);
    char* conc = my_strcon(file, actual->d_name);
    picture_to_double(IMG_Load(conc), (*(input + i))->mat);
    (*(input + i))->expOutput = atoi(actual->d_name);
    i++;
  }
  return input;
}

void training(char* file)
{
  input_t **input = loadInput("trainingPicture/");
  input_t *inp = NULL;
  matrix_t *neuron = mat_create(_NB_INPUT_ + 1, _NB_NEURON_);
  matrix_t *output = mat_create(_NB_NEURON_ + 1, _NB_OUTPUT_);
  mat_rand(neuron);
  mat_rand(output);
  my_read(neuron, output, file);

  double totalErr = 0.0, save = 0.0, localErr = 0.0;
  int count = 1;

  do
  {
    save = totalErr;
    for(int i = 0; i < _NB_TRAINING_; ++i)
    {
      inp = *(input + i);
      work(inp->mat, neuron, output);
      localErr = back_prop(inp->expOutput, neuron, output);
      printf("RESULTAT : LOLI FAIS LE\n");
      totalErr += localErr;
    }
    printf("Total error : %g\n", totalErr/count);
    count++;
    if(!(count % 100))
      my_write(neuron, output, "training");
  } while(totalErr != save || totalErr/count < 0.0);
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
  for(int i = 0; i < output->width; ++i)
    printf("%g ", output->output[i]);

  mat_free(neuron);
  mat_free(output);
}
