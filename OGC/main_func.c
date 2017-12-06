#include <stdio.h>
#include <stdlib.h>

#include "file_func.h"
#include "mat_func.h"
#include "ocr_func.h"

#define _NB_NEURON_ 36
#define _NB_INPUT_ 16*16
#define _NB_OUTPUT_ 26
#define _NB_TRAINING_ 52

matrix_t** loadInput()
{
  matrix_t **input = NULL;
  /*matrix_t *input = code de raphi -> tableau des donnée d'entrainement +
   * output de ces donnees, hf moi du futur parce que le moi du present a 
   * franchement aps envie de le code
   */
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
