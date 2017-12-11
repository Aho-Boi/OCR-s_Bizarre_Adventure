#include <dirent.h>
#include <err.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "load_picture.h"
#include "ogc_func.h"
#include "my_string.h"
#include "pixel_color.h"

static
void picture_to_double(SDL_Surface *surface, int *input)
{
  set_pixel_gray(surface);
  binarize_otsu(surface);
  for(int x = 0; x < surface->h; ++x)
    for(int y = 0; y < surface->w; ++y)
      input[x * surface->w +y] = (getpixel(surface, x, y) == 0);
}
 
void loadInput(int *input, int *exp)
{
  DIR *rep = opendir("trainingPicture/");
  if(!rep)
    errx(1, "Could not load image training");
  struct dirent *actual;

  for(int i = 0; i < _NB_INPUT_ + 2;)
  {
    actual = readdir(rep);
    if(actual->d_name[0] == '.')
      continue;
    char *dir = "trainingPicture/";
    char *conc = my_strcon(dir, actual->d_name);
    int l = atoi(actual->d_name);
    exp[i] = l;
    picture_to_double(IMG_Load(conc), input + (i * _LENI_));
    i++;
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    errx(1, "Choose training(1) or generalization(2)");

  srand(time(NULL));

  neuron *hidden = neuron_init(_LENH_, _LENI_);
  neuron *output = neuron_init(_LENO_, _LENH_);

  int *input = malloc(_NB_INPUT_ * _LENI_ * sizeof(int));
  int *exp = malloc(_NB_INPUT_ * sizeof(int));

  loadInput(input, exp);
  FILE *file = NULL;
// training
  if (*argv[1] == '1')
  {
       file = fopen("training", "r");
    if(file)
    {
      char *content = malloc(100000*sizeof(char));
      freadP(content, 100000, file);
      loadWeight(hidden, output, content);
      fclose(file);
    }

    double localErr = 0.0;
    double totalErr = 0.0, save = 0.0;
    int count = 1;

    do
    {
      save = totalErr;
      for(int j = 0; j < _NB_INPUT_; ++j)
      {
	localErr = work(input + j * _LENI_, exp[j], hidden, output);
	double oe = output->exit;
	printf("RESULT FOR %d = %f : LocalErr = %f\n", j, oe, localErr);
	adaptWeight(localErr, input + j * _LENI_, hidden, output);
	totalErr += localErr;
      }
      printf("Total error : %g\n", totalErr/count);
      count += 1;
      if(!(count % 999))
      {
        file = fopen("training", "w");
	fwriteP(hidden, output, file);
	fclose(file);
      }
    }while(/*totalErr != save || totalErr/count < 0.0*/count < _NB_TURN_);

    file = fopen("training", "w");
    fwriteP(hidden, output, file);
    fclose(file);
  }
  // generalization
  else if (*argv[1] == '2')
  {
    file = fopen("training", "r");
    char *content = malloc(1000000000*sizeof(char));
    freadP(content, 1000000000, file);
    loadWeight(hidden, output, content);
    fclose(file);
/*
    printf("Enter the test: ");
//    int input[3] = {0, 0, 0};
    int i = 0;
    scanf("%d", &i);
    work(input + i * _LENI_, i, hidden, output);
    printf("%f", output->exit);
*/
    printf("Enter the name of file to test: ");
    char *nf = malloc(100 * sizeof(char));
    scanf("%s", nf);
    int *g = malloc(_LENI_ * sizeof(int));
    picture_to_double(IMG_Load(nf), g);
    work(g, 36, hidden, output);
    printf("%f", output->exit);
  }
  else
  {
    free(hidden);
    errx(1, "Invalid argument");
  }

  free(hidden);
}
