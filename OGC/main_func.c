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

static
matrix_t** loadInput()
{
  matrix_t **input = malloc(sizeof(matrix_t*) * _NB_TRAINING_);
  int i = 0;
  DIR *rep = opendir("./training");
  if(!rep)
    errx(1, "Could not load image training");
  struct dirent *actual;

  while((actual = readdir(rep)) != NULL)
  {
    *(input + i) = mat_create(5, 5);
    char* conc = my_strcon("training/", actual->d_name);
    picture_to_double(IMG_Load(conc), *input + i);
    i++;
  }
  return input;
}

void training(char* file)
{
  matrix_t **input = loadInput();
  matrix_t *neuron = mat_create(_NB_INPUT_ + 1, _NB_NEURON_);
  matrix_t *output = mat_create(_NB_NEURON_ + 1, _NB_OUTPUT_);
  my_read(neuron, output, file);

  double totalErr = 0.0, save = 0.0, localErr = 0.0;
  int count = 1;

  do
  {
    save = totalErr;
    for(int i = 0; i < _NB_TRAINING_; ++i)
    {
      work(input[i], neuron, output);
      localErr = back_prop(/*expOutput*/36, neuron, output);
      printf("RESULTAT : LOLI FAIS LE");
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
  matrix_t **input = loadInput();
  matrix_t *neuron = mat_create(_NB_INPUT_ + 1, _NB_NEURON_);
  matrix_t *output = mat_create(_NB_NEURON_ + 1, _NB_OUTPUT_);
  my_read(neuron, output, file);
  work(input[0], neuron, output);
  /*Print la sortie flemme too*/

  mat_free(neuron);
  mat_free(output);
}
