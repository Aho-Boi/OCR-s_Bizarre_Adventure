#include <stdio.h>
#include <stdlib.h>

#include "file_func.h"
#include "mat_func.h"
#include "ocr_func.h"

#define _NB_NEURON_
#define _NB_INPUT_
#define _NB_OUPUT_
#define _NB_TRAINING_


void training(char* file)
{
  matrix_t *neuron = mat_create(_NB_INPUT_ + 1, _NB_NEURON_);
  matrix_t *output = mat_create(_NB_NEURON_ + 1, _NB_OUTPUT_);
  read(neuron, output, file);

  /*matrix_t *input = code de raphi -> tableau des donnée d'entrainement +
   * output de ces donnees, hf moi du futur parce que le moi du present a 
   * franchement aps envie de le code
   */
  double totalErr = 0.0, save = 0.0, localErr = 0.0;
  int count = 1;

  do
  {
    save = totalErr;
    for(int i = 0, i < _NB_TRAINING_; ++i)
    {
      work(input[i], neuron, output);
      localErr = back_prop(expOutput, neuron, output);
      printf("RESULTAT : LOLI FAIS LE");
      totalErr += localErr;
    }
    printf("Total error : %g\n", totalErr/count);
    count++;
    if(!(count % 100))
      write(neuron, output, "training");
  } while(totalErr != save || totalErr/count < 0.0);
  write(neuron, output, "training");

  mat_free(neuron);
  mat_free(output);
}

void generalization(char *file)
{
  matrix_t *neuron = mat_create(_NB_INPUT_ + 1, _NB_NEURON_);
  matrix_t *output = mat_create(_NB_NEURON_ + 1, _NB_OUTPUT_);
  read(neuron, output, file);
  /*Coder le truc qui va charger input*/
  work(input, neuron, output);
  /*Print la sortie flemme too*/

  mat_free(neuron);
  mat_free(output);
}
